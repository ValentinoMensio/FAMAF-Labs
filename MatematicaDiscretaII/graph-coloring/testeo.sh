if [ $# -eq 0 ]
  then
    echo "Uso: ./testeo.sh <directorio del grafo>"
    echo
    exit 1
fi

########## Script para testear el funcionamiento de la estructura ##########
# run gcc
gcc -g -Wall -Wextra -O2 -std=c99 -o test src/APIParte2.c src/APIG23.c src/main.c src/datosGrafo.c src/datosVertices.c src/lectura.c src/depurar.c src/hash.c src/ordenamiento.c

# run test for the param 1
time ./test < $1

# preguntar si queremos ejecutar el testeo con valgrind
echo "Valgrind? (y/n)"
read valgrind
if [[ $valgrind = "y" || $valgrind = "Y" || $valgrind = "yes" || $valgrind = "YES" ]]
  then
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test < $1
else
  echo "No se ejecutara valgrind"
fi
rm -rf test