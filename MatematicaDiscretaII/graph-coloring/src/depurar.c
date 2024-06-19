#include "depurar.h"

// Funciones que proveen seguridad en el codigo

int 
chequeoNulo(void *ptr){
    if (ptr == NULL) {
        printf("Error puntero nulo\n");
        return 1;
    }
    return 0;
}

int 
chequeoColoreoPropio(Grafo grafo, u32 *Color) {
    for (u32 i = 0; i < NumeroDeVertices(grafo); i++) {
        for (u32 j = 0; j < Grado(i, grafo); j++) {
            u32 w = IndiceVecino(j, i, grafo); // Obtener el índice de vecino de v
            if (Color[w] == Color[i]) {
                printf ("Error: %d y %d tienen el mismo color (%d)\n", i, w, Color[i]);
                return 1;
            }
        }
    }
    return 0;
}

void 
liberarSeguro(void *ptr) {
    if (ptr != NULL) {
        free(ptr);
    }
}

Grafo 
errorTerminal(char *msg, Grafo grafo) {
    printf("%s\n", msg);
    DestruirGrafo(grafo);
    return NULL;
}

// Funciones de muestra para control o depuracion

void 
mostrarInfo(Grafo grafo) {
    printf("Numero de vertices: %u\n", NumeroDeVertices(grafo));
    printf("Numero de lados: %u\n", NumeroDeLados(grafo));
    printf("Grado maximo: %u\n", Delta(grafo));
}

void 
mostrarGrados(Grafo grafo) {
    for (u32 i = 0; i < NumeroDeVertices(grafo); i++) {
        printf("Grado de %u: %u\n", Nombre(i, grafo), Grado(i, grafo));
    }
}