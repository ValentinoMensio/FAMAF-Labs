#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "parsing.h"
#include "parser.h"
#include "command.h"

#include "assert.h"

static scommand parse_scommand(Parser p) {
    assert(p != NULL);
    scommand result = scommand_new();
    arg_kind_t type;
    char *str;
    parser_skip_blanks(p);
    str = parser_next_argument(p, &type);
    while(str != NULL){ /* Bucle hasta que parse_next_argument no tenga que devolver*/
        if(type == ARG_NORMAL){
            scommand_push_back(result,str);
        }
        if(type == ARG_INPUT){
            scommand_set_redir_in(result,str);
            if(scommand_get_redir_in(result) == NULL){ /* Hay un < pero no tiene una dirección */
                scommand_destroy(result);
                break;
            }
        }
        if(type == ARG_OUTPUT){
            scommand_set_redir_out(result, str);
            if(scommand_get_redir_out(result) == NULL){ /* Hay un > pero no tiene una dirección */
                scommand_destroy(result);
                break;
            }
            
        }
        str = parser_next_argument(p, &type);
    }
    /* MUCHOS CASOS DE ERROR -> Caso en donde no se completa el comando, ie el comando queda a medias.
                                Caso en donde se inyecta ruido */

    /* Devuelve NULL cuando hay un error de parseo */
    return result;
}

pipeline parse_pipeline(Parser p) {
    assert(p != NULL);
    assert(!parser_at_eof(p));

    pipeline result = pipeline_new();
    scommand cmd = scommand_new();
    bool error = false, another_pipe=true;

    bool garbage, background_op;

    /* help */
    parser_skip_blanks(p);
    cmd = parse_scommand(p);
    
    error = (scommand_is_empty(cmd)); /* Comando inválido al empezar */

    while (another_pipe && !error) {
        
        pipeline_push_back(result, cmd);
        parser_op_background(p, &background_op);
        parser_op_pipe(p, &another_pipe);
        if(another_pipe && !error){
            parser_skip_blanks(p);
            cmd=parse_scommand(p);
        }
        error = (scommand_is_empty(cmd));
    }
    parser_garbage(p, &garbage);
    if(background_op && !error){
        pipeline_set_wait(result, false);
    }
    if(error){
        result=NULL;
    }

    /* Opcionalmente un OP_BACKGROUND al final */
    
    /* Tolerancia a espacios posteriores */
    /* Consumir todo lo que hay inclusive el \n */
    /* Si hubo error, hacemos cleanup */
    return result; // MODIFICAR

}


