#ifndef APIG23_H
#define APIG23_H

#include <stdio.h>
#include <stdlib.h>
#include "EstructuraGrafo23.h"

/*
 * Estructura que representa al grafo.
 */
typedef GrafoSt *Grafo;

// Funciones de construccion y destruccion del grafo

/*
 * Construye un grafo a partir de la lectura del stdin.
 * Devuelve NULL si no pudo construir el grafo.
 */
Grafo ConstruirGrafo();

/*
 * Destruye el grafo y libera toda la memoria asociada
 * de forma segura, no libera memoria si no es necesario.
 */
void DestruirGrafo(Grafo grafo);

// Funciones de consulta del grafo

u32 NumeroDeVertices(Grafo grafo);
u32 NumeroDeLados(Grafo grafo);
u32 Delta(Grafo grafo);


// Funciones de consulta de los lados-vertices

/*
 * Devuelve el nombre del vertice i-esimo del grafo
 * Precondicion: i < NumeroDeVertices(grafo)
 */
u32 Nombre(u32 i,Grafo grafo);

/*
 * Devuelve el grado del vertice i-esimo del grafo
 * Precondicion: i < NumeroDeVertices(grafo)
 */
u32 Grado(u32 i,Grafo grafo);

/*
 * Devuelve el id del vertice j-esimo vecino del vertice i-esimo
 * Precondicion: i < NumeroDeVertices(grafo)
 * Precondicion: j < Grado(i,grafo)
 */
u32 IndiceVecino(u32 j,u32 i,Grafo grafo);


#endif
