#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "strextra.h"
#include "command.h"
#include <assert.h>

struct scommand_s {// estructura de la forma [*char], *char, *char
    GSList *arr;
    char * in;
    char * out;
};

scommand scommand_new(void){
    scommand new = malloc(sizeof(struct scommand_s));
    new->arr = NULL;
    new->in = NULL;
    new->out = NULL;
    
    return new;
}

scommand scommand_destroy(scommand self){
    assert(self != NULL);
    g_slist_free_full(self->arr, free);
    self->arr = NULL;
    free(self->in);
    self->in = NULL;
    free(self->out);
    self->out = NULL;
    free(self);
    self = NULL;
    assert(self == NULL);
    return self;
}

void scommand_push_back(scommand self, char * argument){
    assert(self != NULL && argument != NULL);
    self->arr = g_slist_append(self->arr,argument);
    assert(!scommand_is_empty(self));
}

void scommand_pop_front(scommand self){
    assert(self != NULL && !scommand_is_empty(self));
    gpointer h = g_slist_nth_data(self->arr, 0);
    self->arr = g_slist_remove(self->arr,h);
    free(h);
}

void scommand_set_redir_in(scommand self, char * filename){
    assert(self != NULL);
    self->in = filename;
}

void scommand_set_redir_out(scommand self, char * filename){
    assert(self != NULL);
    self->out = filename;
}

bool scommand_is_empty(const scommand self){
    assert(self != NULL);
    return scommand_length(self) == 0;
}

unsigned int scommand_length(const scommand self){
    assert(self != NULL);
    return g_slist_length(self->arr);
}

char * scommand_front(const scommand self){
    assert(self != NULL && !scommand_is_empty(self));
    char *head = g_slist_nth_data(self->arr, 0);
    assert(head!=NULL);
    return head;
}

char * scommand_get_redir_in(const scommand self){
    assert(self != NULL);
    return self->in;
}

char * scommand_get_redir_out(const scommand self){
    assert(self != NULL);
    return self->out;
}

char * scommand_to_string(const scommand self){
    assert(self != NULL);
    GSList* aux = self->arr; // copio en un auxiliar para no modificar a la lista
    char * str = NULL;
    str = strdup("");
    if (aux != NULL){
        str = strmerge(str, aux->data);
        aux = aux->next;
        while (aux != NULL){
            str = strmerge(str, " ");
            str = strmerge(str, g_slist_nth_data(aux,0u));
            aux = aux->next;
        }
    } 
    if(self->out != NULL){
        str = strmerge(str, " > ");
        str = strmerge(str, self->out);
    }
    if (self->in != NULL){
        str = strmerge(str," < ");
        str = strmerge(str, self->in);
    }
    assert(scommand_is_empty(self) || scommand_get_redir_in(self)==NULL || scommand_get_redir_out(self)==NULL || strlen(str)>0);
    return str;
}

struct pipeline_s { // estructura de la forma [scommand], bool
    GSList * arr;
    bool b; 
};

pipeline pipeline_new(void){
    pipeline new = malloc(sizeof(struct pipeline_s));
    new->arr = NULL;
    new->b = true;
    assert(new != NULL && pipeline_is_empty(new) && pipeline_get_wait(new));
    return new;
}

static void scommand_destroy_void(void* self){
    scommand s2 = self;
    scommand_destroy(s2);
}

pipeline pipeline_destroy(pipeline self){
    assert(self != NULL);
    g_slist_free_full(self -> arr, scommand_destroy_void);
    self -> arr = NULL;
    free(self);
    self = NULL;
    assert(self == NULL);
    return self;
}

void pipeline_push_back(pipeline self, scommand sc){
    assert(self != NULL && sc != NULL);
    self->arr = g_slist_append(self->arr, sc);
    assert(!pipeline_is_empty(self));
}

void pipeline_pop_front(pipeline self){
    assert(self != NULL);
    gpointer h = g_slist_nth_data(self->arr, 0);
    self->arr = g_slist_remove(self->arr,h);
    scommand_destroy(h);
}

unsigned int pipeline_length(const pipeline self){
    assert(self != NULL);
    return g_slist_length(self -> arr);
}

void pipeline_set_wait(pipeline self, const bool w){
    assert(self != NULL);
    self->b = w;
}

bool pipeline_is_empty(const pipeline self){
    assert(self != NULL);
    return (self->arr == NULL);
}

scommand pipeline_front(const pipeline self){
    assert(self != NULL && !pipeline_is_empty(self));
    scommand fst_command = g_slist_nth_data(self -> arr, 0);
    assert(fst_command != NULL);
    return fst_command;
}   

bool pipeline_get_wait(const pipeline self){
    assert(self != NULL);
    return self -> b;
}

char * pipeline_to_string(const pipeline self){
    assert(self!=NULL);
    GSList *aux = self->arr;
    char * str = NULL;
    str = strdup("");
    if(aux != NULL){
        char* m = scommand_to_string(g_slist_nth_data(aux,0u));
        str = strmerge(str,m);
        free(m);
        m = NULL;
        aux = aux->next;
        while (aux != NULL){
            str = strmerge(str, " | ");
            char* m = scommand_to_string(g_slist_nth_data(aux,0u));
            str = strmerge(str,m);
            free(m);
            m = NULL;
            aux = aux->next;
        }
        if (!pipeline_get_wait(self)){
            str = strmerge(str, " & ");
        }               
    }
    assert(pipeline_is_empty(self) || pipeline_get_wait(self) || strlen(str)>0);
    return str;
}