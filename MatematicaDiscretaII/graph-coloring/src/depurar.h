#ifndef DEPURAR_H
#define DEPURAR_H

#include <stdio.h>
#include "APIG23.h"

/*
 * Funcion que imprime un mensaje de error si el puntero es nulo
 * y devuelve 1, si no solo devuelve 0
 */
int chequeoNulo(void *ptr);

/*
 * Funcion que chequea si el coloreo del grafo es propio
 * Devuelve 1 si no lo es, 0 si lo es
 */
int chequeoColoreoPropio(Grafo grafo, u32 *Color);

/*
 * Funcion que libera un puntero si no es nulo
 */
void liberarSeguro(void *ptr);

/*
 * Funcion que imprime un mensaje de error y destruye el grafo
 */
Grafo errorTerminal(char *msg, Grafo grafo);

/*
 * Funcion que muestra la informacion del grafo
 * N, M y delta
 */
void mostrarInfo(Grafo grafo);

/*
 * Funcion que muestra los grados de cada vertice
 */
void mostrarGrados(Grafo grafo);

#endif