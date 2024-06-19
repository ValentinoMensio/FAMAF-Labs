#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/wait.h>
#include "command.h"
#include "execute.h"
#include "parser.h"
#include "parsing.h"
#include "builtin.h"
#include "prompt.h"

int main(int argc, char *argv[]) {
    pipeline pipe;
    Parser input;
    bool quit = false;
    while (!quit) {
        input = parser_new(stdin);
        show_prompt();
        while(waitpid(-1,NULL,WNOHANG) > 0);
        pipe = parse_pipeline(input);
        quit = parser_at_eof(input);

        if (pipe != NULL){
            execute_pipeline(pipe);
            pipeline_destroy(pipe);
        }
    }
    printf("\n"); // salto antes de salir
    parser_destroy(input); input = NULL;
    return EXIT_SUCCESS;
}

