#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "APIG23.h"
#include "APIParte2.h"
#include "depurar.h"

// Funcion interna para liberar memoria
static void liberarMemoria(Grafo grafo, u32 *Orden1, u32 *Orden2, u32 *Color1, u32 *Color2) {
    liberarSeguro(Color1);
    liberarSeguro(Color2);
    liberarSeguro(Orden1);
    liberarSeguro(Orden2);
    DestruirGrafo(grafo);
}

int main(void) {

    Grafo grafo = ConstruirGrafo();
    if (grafo == NULL) {
        return 1;
    }

    u32 *Orden1 = malloc(NumeroDeVertices(grafo) * sizeof(u32));
    u32 *Orden2 = malloc(NumeroDeVertices(grafo) * sizeof(u32));
    
    for (u32 i = 0; i < NumeroDeVertices(grafo); i++) {
        Orden1[i] = i;
        Orden2[i] = i;
    }

    u32 *Color1 = calloc(sizeof(u32), NumeroDeVertices(grafo));
    u32 *Color2 = calloc(sizeof(u32), NumeroDeVertices(grafo));

    u32 cantcolor1 = Greedy(grafo, Orden1, Color1);
    printf("Primera ejecucion de Greedy, orden natural\n");
    printf ("Cantidad de colores iniciales: %u\n", cantcolor1);
    printf ("----------------------------------------\n");

    memcpy(Color2, Color1, NumeroDeVertices(grafo) * sizeof(u32));
    u32 cantcolor2 = cantcolor1;
    

    u32 *auxColor = malloc(NumeroDeVertices(grafo) * sizeof(u32));
    
    for (int i = 0; i < 32; i++){
        // Usamos fork() para correr ordenparimpar y ordenjedi paralelamente
        // Se corre 16 veces cada orden y se intercambian los arrays de coloreo
        // Cada orden espera al otro para continuar
        pid_t pid = fork();
        
        if (pid < 0) {
            printf("Error: fork fallido\n");
            exit(EXIT_FAILURE);
        }
        
        else if (pid == 0){
            // Proceso hijo, corre orden jedi

            for (int j = 0; j < 16; j++){
                if (OrdenJedi(grafo, Orden1, Color1) == 0){
                    cantcolor1 = Greedy(grafo, Orden1, Color1);
                }
                else{
                    printf("Error en orden Jedi\n");
                    goto fin;
                }
            }
            
            liberarMemoria(grafo, Orden1, Orden2, Color1, Color2);
            liberarSeguro(auxColor);
            exit(EXIT_SUCCESS);
        }
        else{
            // Proceso padre, corre orden impar-par

            for (int k = 0; k < 16; k++){
                if (OrdenImparPar(NumeroDeVertices(grafo), Orden2, Color2) == 0){
                    cantcolor2 = Greedy(grafo, Orden2, Color2);
                }
                else{
                    printf("Error en orden impar-par\n");
                    goto fin;
                }
            }
            wait(NULL);
        }

        // Una vez terminaron ambos intercambiamos los arrays de coloreo
        memcpy(auxColor, Color1, NumeroDeVertices(grafo) * sizeof(u32));
        memcpy(Color1, Color2, NumeroDeVertices(grafo) * sizeof(u32));
        memcpy(Color2, auxColor, NumeroDeVertices(grafo) * sizeof(u32));
        //printf("Coloreo minimo en la iteracion %u: %u\n", i+1, cantcolor1 < cantcolor2 ? cantcolor1 : cantcolor2);
    }
    liberarSeguro(auxColor);
   

    // Imprimimos la menor cantidad de colores conseguida
    printf("Minima cantidad de colores obtenida: %u\n", cantcolor1 < cantcolor2 ? cantcolor1 : cantcolor2);
    
fin:
    liberarMemoria(grafo, Orden1, Orden2, Color1, Color2);
    return 0;
}