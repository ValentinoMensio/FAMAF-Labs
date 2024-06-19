#ifndef __APIP2_H
#define __APIP2_H

#include "APIG23.h"


/*
 * Corre Greedy en el orden dado por Orden, cargando el coloreo en Color y
 * devolviendo el numero de colores usado.
 */
u32 Greedy(Grafo G,u32* Orden,u32* Color);

/*
 * Ordena indices poniendo primero los indices de color el mayor impar,
 * luego los indices de color el segundo mayor impar, etc hasta terminar
 * con los impares, y luego pone los indices de color el mayor par, luego
 * el segundo mayor par, etc. Aca no es necesaria la estructura de G, solo n.
 */
char OrdenImparPar(u32 n,u32* Orden,u32* Color);

/*
 * Ordena indices poniendo primero los indices con la mayor fuerza Jedi,
 * donde la fuerza Jedi es el resultado de calcular la suma de los grados de
 * los vertices de un mismo color, multiplicados por el numero de color.
 * Es necesaria la estructura de G para poder calcular la fuerza Jedi.
 */
char OrdenJedi(Grafo G,u32* Orden,u32* Color);

#endif