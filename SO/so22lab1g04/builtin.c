#include <assert.h>
#include <stdbool.h>
#include <glib.h>
#include <string.h>
#include "builtin.h"
#include "command.h"
#include "unistd.h"
#include "strextra.h"
#include <stdio.h>

struct scommand_s {// estructura de la forma [*char], *char, *char
    GSList *arr;
    char * in;
    char * out;
};

static void cd_builtin_run(scommand cmd){
    assert(cmd != NULL);
    unsigned int n = scommand_length(cmd);
    char* home_path = getenv("HOME"); //escriben en home_path "home/usuario
    if (n > 2) {
        printf("Muchos argumentos\n");  /* Aviso de exceso de args */
    }
    else if (n == 2) {
        scommand_pop_front(cmd);
        char* path = scommand_front(cmd);
        int err = chdir(path);
        if (err < 0) {
            printf("No se encontró el directorio\n");
        }
    }
    else if (n == 1) {
        int err = chdir(home_path);
        if (err < 0) {
            printf("error\n");
        }
    }
}

static void exit_builtin_run(scommand cmd){
	assert(builtin_is_internal(cmd));
	scommand_destroy(cmd);
	exit(0);
}

static void help_builtin_run(scommand cmd){
	assert(builtin_is_internal(cmd));
	printf("Nombre del shell: Mybash \n Autores: Valentino Mensio, Mauricio José Pintos, Tomas Martinez y Juana Balduini \n Comandos internos: Cd: El comando interno cd nos permite poder cambiar de directorios. \n Help: El comando interno help nos permite ver información de la shell(nombre de la misma, autores y comandos internos que puede ejecutar\n)");
}


static bool str_cmpre(const char* s_1, const char* s_2){
    bool result = false; 
    if(0 == strcmp(s_1,s_2)){
        result = true; 
    }
    return result;
}

bool builtin_is_internal(scommand cmd){
    char* is_internal = scommand_front(cmd);
    return (str_cmpre(is_internal,"cd") || str_cmpre(is_internal,"exit") || str_cmpre(is_internal,"help"));
}

bool builtin_alone(pipeline p){
    assert(p != NULL);
	scommand front = pipeline_front(p);
    bool value = builtin_is_internal(front);
    bool length = (pipeline_length(p) == 1);
    assert(pipeline_length(p) == 1 && builtin_is_internal(pipeline_front(p)));
    return value && length;
}

void builtin_run(scommand cmd){
    assert(builtin_is_internal(cmd));
	if (str_cmpre(scommand_front(cmd),"cd")) {
		cd_builtin_run(cmd);
	}
	else if (str_cmpre(scommand_front(cmd),"exit")){
		exit_builtin_run(cmd);
	}
	else if(str_cmpre(scommand_front(cmd),"help")){
		help_builtin_run(cmd);
	}
}