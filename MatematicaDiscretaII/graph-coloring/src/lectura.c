#include <stdio.h>
#include "APIG23.h"


void
leerLinea(){
    char c;
    while(scanf("%c", &c) != 0 && c != '\n');
}

int 
leerEncabezado(u32 *N, u32 *M){
    char c;
    if (scanf("%c", &c) == 0) {
        printf("Error, archivo no valido/dañado/vacio.\n");
        return 1;
    }
    
    while(c != EOF){
        if (c != 'p') {
            if (c != 'c' && c != 'e') {
                // Si el primer caracter de la linea no es 'p', 'c' o 'e', error
                printf("Error en el formato DIMACS. Linea comienza con: %c\n", c);
            }
            // Si la linea no es el encabezado, saltar la linea entera
            leerLinea();
            // Leer el primer char de la siguiente linea
            if (scanf("%c", &c) == EOF) {
                printf("Error al leer el siguiente caracter de la entrada\n");
                return 1;
            }
        }
        else{
            // Si la linea es el encabezado, leerla y salir
            if(scanf(" edge %u %u", N, M) != 2) {
                printf("Error en el formato del encabezado\n");
                return 1;
            }
            break;
        }
    }
    return 0;
}