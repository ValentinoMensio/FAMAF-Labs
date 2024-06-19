
#ifndef LECTURA_H
#define LECTURA_H

#include <stdio.h>
#include "EstructuraGrafo23.h"

// Funciones de lectura de archivos

/*
 * Avanza el cursor del archivo hasta el final de la linea actual.
 */
void leerLinea();

/*
 * Lee el encabezado del archivo y guarda los valores en N y M.
 * Devuelve 1 si hubo un error, 0 si no.
 */
int leerEncabezado(u32 *N, u32 *M);


#endif