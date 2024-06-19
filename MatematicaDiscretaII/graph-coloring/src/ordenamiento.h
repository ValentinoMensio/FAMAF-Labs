
#ifndef SORT_H
#define SORT_H

#include "EstructuraGrafo23.h"
#include "APIG23.h"

/*
 * Funcion que ordena los lados del grafo por el metodo de ordenamiento
 * radix. Se ordenan los lados por el primer vertice del lado.
 * Recibe el arreglo de lados y la cantidad de lados
 */
void radixSort(lado *grafoLados, u32 M2);

#endif