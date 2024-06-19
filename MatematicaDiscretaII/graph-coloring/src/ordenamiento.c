#include <string.h>

#include "ordenamiento.h"
#include "depurar.h"

/*
 * Funcion para obtener el maximo valor de un arreglo de lados.
 */
static u32 getMax(lado *lados, u32 M2) {
    u32 max = lados[0].fst;
    for (u32 i = 1u; i < M2; i++)
        if (lados[i].fst > max)
            max = lados[i].fst;
    return max;
}


/*
 * Funcion para pre-ordenar un arreglo de lados usando counting sort.
 */
static void countingSort(lado *lados, u32 M2, unsigned long dec) {
    lado *output = malloc(sizeof(lado) * M2);
    if (chequeoNulo(output)) {
        printf("Error al reservar memoria para output\n");
        return;
    }

    // Obtener el maximo dec.
    u32 max = (lados[0].fst / dec) % 10;
    for (u32 i = 1; i < M2; i++) {
        if (((lados[i].fst / dec) % 10) > max){
            max = (lados[i].fst / dec) % 10;
        }
    }

    u32 count[10];
    memset(count, 0, sizeof(count));

    // Calcular el conteo de elementos.
    for (u32 i = 0; i < M2; i++){
        count[(lados[i].fst / dec) % 10]++;
    }
    // Calcular el conteo acumulativo. (parecido a nuestro grafo->ref)
    for (u32 i = 1; i < 10; i++){
        count[i] += count[i - 1];
    }

    // Colocar los elementos en orden, dependiendo de dec.
    for (int i = M2-1; i >= 0; i--) {
        output[count[(lados[i].fst / dec) % 10] - 1] = lados[i];
        count[(lados[i].fst / dec) % 10]--;
    }

    // Copiar el arreglo ordenado al arreglo original.
    for (u32 i = 0; i < M2; i++){
        lados[i] = output[i];
    }

    free(output);
}


void radixSort(lado *grafoLados, u32 M2) {
    // Obtener maximo entre los lados
    u32 max = getMax(grafoLados, M2);

    // Aplicar counting sort para ordenar elementos basandose en el valor dec
    for (unsigned long dec = 1; dec <= max; dec *= 10){
        countingSort(grafoLados, M2, dec);
    }
}
