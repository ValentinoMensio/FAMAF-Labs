#include "APIG23.h"

u32
Nombre(u32 i,Grafo grafo){
    return grafo->lados[grafo->ref[i]].fst;
}

u32
Grado(u32 i,Grafo grafo){
    if(i >= grafo->N){
        return UINT32_MAX;
    }
    else{
       if (i == 0) {
           return grafo->ref[i] + 1;
        }
        else{
           return grafo->ref[i] - grafo->ref[i-1];
        }
    } 
}

u32
IndiceVecino(u32 j,u32 i,Grafo grafo){
    if(j > Grado(i,grafo) || i >= grafo->N){
        return UINT32_MAX;
    }
    else{
        return grafo->traductor[i][j];
    }
}