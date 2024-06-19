# Laboratorio 4

------

- Pintos, Mauricio
- Longhi, Fabrizio
- Martinez, Tomas
- Mensio, Valentino

------

[TOC]

------

## Respondiendo las preguntas



###  Cuando se ejecuta el main con la opción -d, ¿qué se está mostrando en la pantalla?

Cuando se ejecuta el main con la opción -d, lo que sucede es que FUSE entra en un "debug mode". 

Se muestran en pantalla las operaciones que realiza FUSE a la hora de montar las imagenes, especificando así en donde se encuentra un error o si corre sin problemas.

Como dice el nombre del modo, este modo es útil a la hora de debuggear.  

### ¿Hay alguna manera de saber el nombre del archivo guardado en el cluster 157?

Sí existe una manera de saber el nombre del archivo guardado en el cluster 157 y es la siguiente:

Lógicamente lo primero en nuestra lista de quehaceres es investigar si efectivamente nuestro cluster 157 esta siendo utilizado o no.  Para esto utilizaremos la siguiente función:

```c
bool fat_table_is_cluster_used(fat_table table, u32 cluster);
```

En el caso de que el mismo no este siendo utilizado, no existe archivo que buscar. Por otro lado, si este cluster si es utilizado debemos presenciar más cuestiones. 

Como idea principal debemos recorrer desde el directorio raíz hasta encontrar el archivo guardado en el cluster 157. Para esto, debemos en un primer lugar verificar en que cluster (o clusters) esta guardado nuestro directorio raíz. Por suerte, tenemos la estructura que se nos provee y esto facilita las cosas. 

La estructura nos provee el primer cluster de la cadena que esta vinculado a nuestro directorio o archivo. Con conocer el primer cluster podríamos suponer que la busqueda de los demás clusters vinculados a nuestro archivo estaría pensada apriori de una forma similar a esta: 

```c
...
    
while(cluster != 157 || !fat_table_cluster_is_EOC(cluster)){
    cluster = fat_table_get_next_cluster(table, cluster);
}
```

 

Como podemos ver en el bloque de código, esto solo nos servira para ver en casos particulares. Por eso debemos fijarnos en el directorio de raíz en un primer lugar y luego ingresar más profundo. 

El caso es el mismo para todos los directorios o archivos. En un primer caso, observamos el directorio raíz, luego los archivos de este directorio raíz, y si no se encuentra, los directorios dentro del directorio raíz, así sucesivamente hasta encontrar el cluster 157.

Una vez encontrado el archivo guardado en el cluster 157, nuevamente gracias a la estructura se nos hace posible traducir el nombre, finalizando con la manera que encontramos para descubrir el nombre del archivo. 

### ¿Dónde se guardan las entradas de directorio? ¿Cuántos archivos puede tener adentro un directorio en FAT32?

Las entradas de directorio son almacenadas en el cluster del directorio, es decir que cualquier archivo (o directorio) tiene su entrada de directorio almacenada en el cluster del directorio en donde se encuentra(directorio padre).

Un directorio en FAT32, puede tener hasta 2^16 - 2 archivos (65534).

### Cuando se ejecuta el comando como ls -l, el sistema operativo, ¿llama a algún programa de usuario? ¿A alguna llamada al sistema? ¿Cómo se conecta esto con FUSE? ¿Qué funciones de su código se ejecutan finalmente? 

En un principio en linux, el comando ls utiliza las llamadas al sistema: openat(), getdents() y close().

FUSE hace de interfaz entre el modo usuario y las llamadas a sistema, entonces nosotros cuando usamos ls -l, FUSE busca en la estructura fuse_operations la función (o las funciones) que nos permite utilizar el ls -l. 

En FUSE, utiliza las llamadas al sistema que estan implementadas, es decir en nuestro caso: opendir(), readdir() y getattr().

### ¿Por qué tienen que escribir las entradas de directorio manualmente pero no tienen que guardar la tabla FAT cada vez que la modifican?

Esto se debe a que, las entradas de directorio son escritas directamente a memoria. 

En cambio la tabla FAT es algo que al modificarse no es necesario pasarla directamente a memoria, la tabla FAT es mapeada a memoria con una función que esta implementada en fat_volume.c 

La tabla FAT se puede sobreescribir y seguir trabajando sin tocar a su vez el disco. 

### Para los sistemas de archivos FAT32, la tabla FAT, ¿siempre tiene el mismo tamaño? En caso de que sí, ¿qué tamaño tiene?

No, la tabla FAT no siempre tiene el mismo tamaño, este tamaño varía según la cantidad de entradas que se tengan.

El tamaño de la FAT al ser montado, es inmutable. No es posible realizarle un cambio a su tamaño.

El tamaño de la FAT se da como: 
$$
(Tamaño/512)*4 = FatSpace
$$
 

