CFLAGS = -Wall -Wextra -O2 -std=c99
# Poner los ficheros en una variable

help:
	echo Prueba ejecutando alguna de estas suites:

APIG23.o: APIG23.c
	gcc -c APIG23.c $(CFLAGS) -o APIG23.o

APIParte2.o: APIParte2.c
	gcc -c APIParte2.c $(CFLAGS) -o APIParte2.o

datosGrafo.o: datosGrafo.c
	gcc -c datosGrafo.c $(CFLAGS) -o datosGrafo.o

datosVertice.o: datosVertice.c
	gcc -c datosVertice.c $(CFLAGS) -o datosVertice.o

main.o: main.c
	gcc -c main.c $(CFLAGS) -o main.o



clean:
	rm -rf test*
	rm -rf *.o
	

