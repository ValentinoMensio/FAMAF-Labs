#include "prompt.h"
#include <unistd.h>
#include <stdio.h>

#define ANSI_BLUE "\033[34;2;14;1m"
#define ANSI_WHITE "\033[0m"

void show_prompt(void){
    char prompt[128];
    gethostname(prompt, 128);
    char workdir[128];
    getcwd(workdir,128);

    printf(ANSI_WHITE "%s" ANSI_BLUE ":" ANSI_WHITE "~" ANSI_BLUE "%s" ANSI_WHITE "$ ", prompt, workdir);

    fflush(stdout);
}