#include <stdbool.h>
#include <string.h>

#include "APIParte2.h"
#include "depurar.h"

// Estructura auxiliar para los ordenes
typedef struct {
    u32 indice;
    u32 var;
} ParOrden;

// Función auxiliar para qsort, ordena según var de mayor a menor.
static int comparar(const void *x_void, const void *y_void){
    ParOrden *x = (ParOrden *)x_void;
    ParOrden *y = (ParOrden *)y_void;
    return y->var - x->var;
}

u32 Greedy(Grafo grafo, u32* Orden, u32* Color) {
    u32 n = NumeroDeVertices(grafo);
    for (u32 i = 0; i < n; i++) {
        Color[i] = UINT32_MAX; // Inicializar todo Color a un valor inválido
    }

    u32 cant_colores = 0;
    bool *colores_usados = malloc((n+1) * sizeof(bool));
    if (chequeoNulo(colores_usados)) {
        return UINT32_MAX; // Si no hay memoria, retornar un valor de error
    }

    for (u32 i = 0; i < n; i++) {
        u32 v = Orden[i];
        if (v >= n) {
            return UINT32_MAX;  // Si el índice de vértice es inválido, retornar un valor de error
        }

        // Colorear el vértice v con el primer color disponible
        u32 c = 0;
        memset(colores_usados, false, (cant_colores+1) * sizeof(bool));

        for (u32 j = 0; j < Grado(v, grafo); j++) {
            u32 w = IndiceVecino(j, v, grafo);
            // Chequeamos si el vecino ya fue coloreado
            if (Color[w] < UINT32_MAX) {
                colores_usados[Color[w]] = true;
            }
        }
        while (colores_usados[c] && c <= cant_colores) {
            c++;
        }
        Color[v] = c;

        // Actualizar la cantidad de colores
        if (c > cant_colores) {
            cant_colores = c;
        }
    }
    liberarSeguro(colores_usados);

    return cant_colores + 1; // Sumar 1 porque los colores son 0-indexados
}


char OrdenImparPar(u32 n,u32* Orden,u32* Color){
    u32 cantPares = 0;
    u32 cantImpares = 0;
    
    ParOrden* impares = malloc(n*sizeof(ParOrden));
    ParOrden* pares = malloc(n*sizeof(ParOrden));
    if (chequeoNulo(pares) || chequeoNulo(impares)) {
        return (char)1;
    }
    
    for (u32 i = 0; i < n; i++) {
        if ((Color[i] & 1) == 0) {
            pares[cantPares].indice = i;
            pares[cantPares++].var = Color[i];
        } else {
            impares[cantImpares].indice = i;
            impares[cantImpares++].var = Color[i];
        }
    }
    qsort(pares, cantPares, sizeof(ParOrden), comparar);
    qsort(impares, cantImpares, sizeof(ParOrden), comparar);

    u32 result = 0;
    for (u32 i = 0; i < cantImpares; i++) {
        Orden[result++] = impares[i].indice;
    }
    for (u32 i = 0; i+cantImpares < n; i++) {
        Orden[result++] = pares[i].indice;
    }
    liberarSeguro(pares);
    liberarSeguro(impares);

    // Si se procesaron todos los índices, se retorna 0, sino 1.
    return result == n ? (char)0 : (char)1;
}

char OrdenJedi(Grafo G, u32* Orden,u32* Color){
    u32 n = NumeroDeVertices(G);
    u32* resultadosFJedi = calloc(n, sizeof(u32));
    ParOrden* resultadoPorVertice = malloc(n*sizeof(ParOrden));
    if (resultadosFJedi == NULL || resultadoPorVertice == NULL) {
        return (char)1;
    }

    // Sumar los grados de los vertices i tales que Color[i] == c
    for(u32 i = 0; i < n; i++){
        resultadosFJedi[Color[i]] += (Grado(i, G)) * Color[i];
    }

    // Llenamos el arreglo resultadoPorVertice 
    for(u32 i = 0; i < n; i++){
        resultadoPorVertice[i].indice = i;
        resultadoPorVertice[i].var = resultadosFJedi[Color[i]];
    }

    // Ordenar resultadoPorVertice de acuerdo a var
    qsort(resultadoPorVertice, n, sizeof(ParOrden), comparar);

    for(u32 i = 0; i < n; i++){
        Orden[i] = resultadoPorVertice[i].indice;
    }

    liberarSeguro(resultadosFJedi);
    liberarSeguro(resultadoPorVertice);

    return (char)0;
}