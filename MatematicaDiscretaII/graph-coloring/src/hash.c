#include "hash.h"
#include "depurar.h"


nodo * 
crearNodo(u32 nombre, u32 indice) {
    nodo *nuevo = (nodo*)malloc(sizeof(nodo));
    if (chequeoNulo(nuevo)) {
        printf ("Error al reservar memoria para algun nodo\n");
        return NULL;
    }
    nuevo->nombre = nombre;
    nuevo->indice = indice;
    nuevo->siguiente = NULL;
    return nuevo;
}


u32 
hash(u32 nombre, u32 N) {
    return nombre % N;
}


void 
agregarHash(u32 nombre, u32 indice, nodo **tabla, u32 N) {
    u32 pos = hash(nombre, N); // Posicion en la tabla de hash
    nodo *nuevo = crearNodo(nombre, indice);
    if (tabla[pos] == NULL) {
        tabla[pos] = nuevo;
    } else {
        nodo *aux = tabla[pos];
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
    }
}


u32 
buscar(u32 nombre, nodo **tabla, u32 N) {
    u32 pos = hash(nombre, N);
    nodo *aux = tabla[pos];
    while (aux != NULL) {
        if (aux->nombre == nombre) {
            return aux->indice;
        }
        aux = aux->siguiente;
    }
    return UINT32_MAX;
}


void 
liberarHash(nodo **tabla, u32 N) {
    for (u32 i = 0; i < N; i++) {
        nodo *aux = tabla[i];
        while (aux != NULL) {
            nodo *aux2 = aux;
            aux = aux->siguiente;
            liberarSeguro(aux2);
        }
    }
    liberarSeguro(tabla);
}
