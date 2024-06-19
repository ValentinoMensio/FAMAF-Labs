<h3>Compilación</h3>
Para poder correr el programa primero debemos estar en el directorio correcto, luego hacer un make, donde se genera el ejecutable llamado mybash,y  por último se puede ejecutar con ./mybash


<h3> Implementanción Command.c </h3>

Para implementar el Command.c, nuestro primer acercamiento fue la estructura que llevarian los tipos, _*_Scommand y Pipeline._*_

Comenzando con el primero, el TAD Scommand, tiene tres campos en su estructura.

    struct scommand_s { // estructura de la forma [*char], *char, *char
    
    GSList *arr;
    
    char * in;
    
    char * out;

    };

Donde: 

GSList * arr -> hace referencia a la lista donde se guardan los comandos simples.

char * in -> hace referencia al archivo que tiene el comando como input, si llegase a tener uno.

char * out -> hace referencia al archivo que tiene el comando como output, si llegase a tener uno.

-------------------------------------------------------------------------------------------------------------------------------------

Luego el segundo, el TAD Pipeline, tiene dos campos en su estructura.

    struct pipeline_s { // estructura de la forma [scommand], bool
    
    GSList * arr;
    
    bool b; 

    };

Donde:

GSList * arr -> hace referencia a la lista donde se guardarian los scommand's.

bool b -> hace referencia a si nuestro pipeline se debe ejecutar en modo foreground o background.

-------------------------------------------------------------------------------------------------------------------------------------

Luego de comprender las estructuras de los TADS a implementar, la implementacion de las funciones, nos llevo tiempo pero no complicaciones mayores.

No fueron agregadas nuevas funciones a las ya especificadas en command.h

-------------------------------------------------------------------------------------------------------

<h3> Implementancion Parsing.c </h3>

La complicacion mayor con esta implementacion fue la comprension del TAD Parser. 

Las funciones a implementar eran: 

*parse_scommand* y *parse_pipeline*

parse_scommand tuvo su complejidad comprendiendo bien como funcionaba la función parse_next_argument del TAD Parser.

parse_pipeline llevo su tiempo para pulirlo y poder ejecutar el test correctamente en su totalidad.

No tuvimos la necesidad de implementar funciones auxiliares ni extras a las ya proporcionadas. 

-------------------------------------------------------------------------------------------------------------------------------------

<h3> Implementacion Builtin.c </h3>

El módulo builtin contaba con tres funciones.Una función para determinar si tenía un único comando y si es interno, una función que decide si un comando dado es interno, y luego otra función para poder ejecutar los distintos comandos.

Para la implementación del builtin agregamos funciones auxiliares que nos van a ser de ayuda para luego poder realizar las funciones principales.

-------------------------------------------------------------------------------------------------

En la función: void builtin_run(scommand cmd)utilizamos las siguientes funciones auxiliares
/*Ejecuta el comando interno cd*/
static void cd_builtin_run(scommand cmd)

/*Ejecuta el comando exit que nos permite salir*/
static void exit_builtin_run(scommand cmd)

/*Dicha función nos da información acerca de la shell, autores y una pequeña descripción de lo que hace cada comando interno*/
static void help_builtin_run(scommand cmd)


-------------------------------------------------------------------------------------------------

En la función: bool builtin_is_internal(scommand cmd) utilizamos la siguiente función
/*Nos permite hacer la comparación entre dos comandos, si son iguales y poder determinar si es comando interno*/
static bool str_cmpre(const char* s_1, const char* s_2)


-----------------------------------------------------------------------------------------------------------------------------------

<h3> Implementación Execute.c </h3>

El módulo execute contaba con una sola función en el .h, y ésta se encarga de ejecutar un pipeline. En este archivo utilizamos varias funciones auxiliares para la realización de la misma.

La función principal:
void execute_pipeline(pipeline apipe)

------------------------------------------------------------------------------------------------------
Funciones auxiliares:

/*Función de redireccion entrada / salida*/
static int redirin_redirout(scommand cmd)

/*Función de comando simple */
static int simple_command(scommand cmd)

