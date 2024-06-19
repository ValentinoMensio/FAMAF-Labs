
#ifndef HASH_H
#define HASH_H

#include "EstructuraGrafo23.h"
#include "APIG23.h"
#include "depurar.h"

// Estructura de nodo de la tabla de hash
typedef struct nodo {
    u32 nombre;                 // Nombre del vertice
    u32 indice;                 // Indice del vertice en el arreglo de lados
    struct nodo *siguiente;     // Siguiente nodo en la posicion i-esima
} nodo;

/*
 * Funcion que crea un nodo de la tabla de hash
 * Recibe el nombre del vertice y el indice del vertice en el arreglo de lados
 * Devuelve un puntero al nodo creado
 * La liberacion de memoria queda a cargo del llamador
 */
nodo *crearNodo(u32 nombre, u32 indice);

/*
 * Funcion que calcula la posicion en la tabla de hash
 * Recibe el nombre del vertice y el tamaño de la tabla
 * Devuelve la posicion en la tabla de hash
 */
u32 hash(u32 nombre, u32 N);

/*
 * Funcion que agrega un nodo a la tabla de hash
 * Recibe el nombre del vertice, el indice del vertice en el arreglo de lados,
 * la tabla de hash y el tamaño de la tabla
 */
void agregarHash(u32 nombre, u32 indice, nodo **tabla, u32 N);

/*
 * Funcion que busca un nodo en la tabla de hash
 * Recibe el nombre del vertice, la tabla de hash y el tamaño de la tabla
 * Devuelve el indice del vertice en el arreglo de lados
 * Si no se encuentra el vertice, devuelve UINT32_MAX
 */
u32 buscar(u32 nombre, nodo **tabla, u32 N);

/*
 * Funcion que libera la memoria de la tabla de hash
 * Recibe la tabla de hash y el tamaño de la tabla
 */
void liberarHash(nodo **tabla, u32 N);

#endif