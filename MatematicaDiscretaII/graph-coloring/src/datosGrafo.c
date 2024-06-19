#include "APIG23.h"

//------------------Funciones de consulta------------------
u32
NumeroDeVertices(Grafo grafo){
    return grafo->N;
}

u32
NumeroDeLados(Grafo grafo){
    return grafo->M;
}

u32
Delta(Grafo grafo){
    return grafo->delta;
}