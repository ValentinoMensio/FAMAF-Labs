#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#include <stdint.h>
#include <stdio.h>

// Definiciones de tipos

typedef unsigned int u32;   // Numero 32 bits sin signo

// Estructura de dupla. Util para representar lados del grafo.
typedef struct { 
   u32 fst;
   u32 snd;
} lado;

typedef struct {
    u32 N;              // Numero de vertices
    u32 M;              // Numero de lados
    u32 delta;          // Grado maximo
    lado *lados;        // Lados del grafo
    u32 *ref;           // Ultimo indice de cada vertice en el arreglo de lados
    u32 **traductor;    // Traductor de nombres a indices en el arreglo de lados
} GrafoSt;

#endif