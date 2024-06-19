#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "tests/syscall_mock.h"
#include "execute.h"
#include "builtin.h"
#include "command.h"

#include <sys/wait.h>


static int redirin_redirout(scommand cmd){
	assert(cmd != NULL);

	char *redirin = scommand_get_redir_in(cmd);
	if(redirin){
		int in = open(redirin,O_RDONLY, S_IRUSR);
		if(in == -1){
			perror("El fichero no existe\n");
			return -1;
		}
		dup2(in, STDIN_FILENO);
		close(in);
	}
	char *redirout = scommand_get_redir_out(cmd);
	if(redirout){
		int out = open(redirout, O_CREAT | O_WRONLY | O_TRUNC , S_IRWXU);
		if (out == -1){
			perror("El fichero no existe\n");
			return -1;
		}
		dup2(out,STDOUT_FILENO);
		close(out);
	}
	return 0; 
}

static int simple_command(scommand cmd){
	assert (cmd != NULL);
	int executed = 0;

	if(builtin_is_internal(cmd)){
		builtin_run(cmd);
	}
	else{
		unsigned int length_scommand = scommand_length(cmd);
		char **arg_to_exec = calloc(length_scommand + 1, sizeof(char*));
		for(unsigned int i = 0; i < length_scommand; ++i){
			char *aux = scommand_front(cmd);
			arg_to_exec[i] = strdup(aux);
			scommand_pop_front(cmd);
		}
		int err = execvp(arg_to_exec[0],arg_to_exec);
		if(err == -1){
			perror("Comando Inexistente\n");
			exit(1);
		}
	}
	return executed;
}

void execute_pipeline(pipeline apipe){
	assert(apipe != NULL);
	bool pipe_wait = pipeline_get_wait(apipe);
	if(pipeline_is_empty(apipe)){
		return;
	}
	
	if(builtin_is_internal(pipeline_front(apipe))){
		builtin_run(pipeline_front(apipe));
	}else if(pipeline_length(apipe) == 1){
		pid_t pid = fork();
		if(pid == 0){
			if(redirin_redirout(pipeline_front(apipe)) == -1){
				exit(EXIT_FAILURE);
			}
			if(simple_command(pipeline_front(apipe)) == -1){
				exit(EXIT_FAILURE);
			}
		}
		else if (pid == -1){
			perror("Fork ERROR\n");
		}
		else{
			if(pipe_wait){
				waitpid(pid,NULL,0);
			}
		}
	}else if(pipeline_length(apipe) == 2){
		int vec_pipe[2];
		pipe(vec_pipe);
		scommand cmd1 = pipeline_front(apipe);
		
		assert(cmd1 != NULL);
		pid_t pid2 = fork();

		if(pid2 == 0){
			dup2(vec_pipe[1], STDOUT_FILENO);
			close(vec_pipe[0]);
			close(vec_pipe[1]);

			simple_command(cmd1);
		}

		pipeline_pop_front(apipe);
		scommand cmd2 = pipeline_front(apipe); 

		pid_t pid3 = fork();
		if(pid3 == 0){
			dup2(vec_pipe[0], STDIN_FILENO);
			close(vec_pipe[0]);
			close(vec_pipe[1]);

			simple_command(cmd2);
		}else{ 
			close(vec_pipe[0]);
			close(vec_pipe[1]);
		}
		
		if(pipe_wait){
			waitpid(pid2,NULL,0);
			waitpid(pid3,NULL,0);
		}
	}
	else {
		perror("Length error\n");
	}
}