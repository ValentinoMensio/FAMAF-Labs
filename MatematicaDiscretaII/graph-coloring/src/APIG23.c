#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>

#include "APIG23.h"
#include "depurar.h"
#include "lectura.h"
#include "hash.h"
#include "ordenamiento.h"


// -------------- Funciones de construccion y destruccion --------------
GrafoSt *ConstruirGrafo() {
    // Lectura encabezado

    u32 N, M;
    if (leerEncabezado(&N, &M)) {
        return errorTerminal("Error al leer el encabezado", NULL);
    }

    // ---------------- Reserva de memoria ----------------

    GrafoSt* grafo = (GrafoSt*)malloc(sizeof(GrafoSt));
    if (chequeoNulo(grafo)) {
        return errorTerminal("Error al reservar memoria para el grafo", grafo);
    }

    grafo->lados = (lado*)malloc(sizeof(lado) * M * 2);
    if (chequeoNulo(grafo->lados)) {
        return errorTerminal("Error al reservar memoria para los lados", grafo);
    }

    grafo->ref = (u32*)malloc(sizeof(u32) * N);
    if (chequeoNulo(grafo->ref)) {
        return errorTerminal("Error al reservar memoria para las ref", grafo);
    }

    grafo->traductor = (u32**)malloc(sizeof(u32*) * N);
    if (chequeoNulo(grafo->traductor)) {
        return errorTerminal("Error al reservar memoria para el traductor", grafo);
    }

    // ---------------- Inicializacion del grafo ----------------
    
    grafo->N = N;       // Cantidad de vertices en cabecera
    grafo->M = M;       // Cantidad de lados en cabecera
    grafo->delta = 0u;   // Luego se calcula

    // Lectura de lados
    u32 i = 0u;
    u32 fst, snd;
    while(i < 2*grafo->M && !feof(stdin)){
        leerLinea();
        if(scanf("e %u %u", &fst, &snd) != 2){
            printf("Linea basura\n");
            continue;
        }
        grafo->lados[i].fst = fst;
        grafo->lados[i].snd = snd;
        grafo->lados[i+1].fst = snd;
        grafo->lados[i+1].snd = fst;
        i = i + 2;
    }
    if (i != 2*grafo->M) {
        return errorTerminal("Error al leer los lados", grafo);
    }

    // Dejar listo para leer un posible siguiente grafo
    leerLinea();

    // Ordenar lados
    radixSort(grafo->lados, grafo->M*2);

    // Calculo de referencias y delta
    u32 i_ref = 0u;
    u32 i_lad = 0u;
    while(i_ref < grafo->N-1){
        if (grafo->lados[i_lad].fst != grafo->lados[i_lad+1].fst){
            grafo->ref[i_ref] = i_lad;

            // Calculo de delta
            if (grafo->delta < Grado(i_ref, grafo)){
                grafo->delta = Grado(i_ref, grafo);
            }
            i_ref++;
        }
        i_lad++;
    }

    grafo->ref[grafo->N-1] = grafo->M*2-1;
    u32 grado_ultimo = Grado(grafo->N-1, grafo);
    if (grado_ultimo == 0u){
        /* Hubo al menos un vertice, que no tiene vecinos
         * Suele darse cuando el header del grafo no coincide
         * con la cantidad de lados que se leen
         */
        return errorTerminal("Error al leer los lados", grafo);
    }
    
    // Calculo de delta para el ultimo vertice
    grafo->delta = grado_ultimo > grafo->delta ? grado_ultimo : grafo->delta;

    // ---------------- Traductor ----------------
    // Guardar memoria para tabla hash auxiliar del tipo nodo
    nodo** tablaHash = (nodo**)malloc(sizeof(nodo*) * grafo->N);
    if (chequeoNulo(tablaHash)) {
        return errorTerminal("Error al reservar memoria para la tabla hash", grafo);
    }

    // Inicializar tabla hash auxiliar
    for (u32 i = 0u; i < grafo->N; i++) {
        tablaHash[i] = NULL;
    }

    // Creacion de tabla hash auxiliar
    for (u32 i = 0u; i < grafo->N; i++) {
        agregarHash(Nombre(i, grafo),i, tablaHash, grafo->N);
    }
    
    // Creacion del traductor
    for (u32 i = 0u; i < grafo->N; i++) {
        grafo->traductor[i] = (u32*)malloc(sizeof(u32) * Grado(i, grafo));
        if (chequeoNulo(grafo->traductor[i])) {
            return errorTerminal("Error al reservar memoria para algun subarreglo del traductor", grafo);
        }

        for (u32 j = 0u; j < Grado(i, grafo); j++) {
            u32 nombreVecino = grafo->lados[grafo->ref[i] + 1 - Grado(i, grafo) + j].snd;
            grafo->traductor[i][j] = buscar(nombreVecino, tablaHash, grafo->N);
        }
    }
    // Liberar tabla hash auxiliar
    liberarHash(tablaHash, grafo->N);
    
    return grafo;
}

void DestruirGrafo(Grafo grafo) {
    if (grafo != NULL){
        liberarSeguro(grafo->lados);
        liberarSeguro(grafo->ref);
        if (grafo->traductor != NULL){
            for (u32 i = 0u; i < grafo->N; i++){
                liberarSeguro(grafo->traductor[i]);
            }
            liberarSeguro(grafo->traductor);
        }
        liberarSeguro(grafo);
    }
}
