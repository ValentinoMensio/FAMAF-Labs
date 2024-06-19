<h3> Introducción </h3> 
En este laboratorio se nos hizo implementar llamadas al sistema sobre un sistema de semáforos nombrados, y cargarlas para hacerlas accesibles para el usuario. Luego utilizando este sistema de semáforos, creamos un programa llamado pingpong.

La llamadas al sistema que implementamos son estas: 

_*_sys_sem_open(int sem,int value)_*_

_*_sys_sem_up(int sem)_*_

_*_sys_sem_down(int sem)_*_

_*_sys_sem_close(int sem)_*_

Para implementar el sistema de semáforos, tuvimos que crear una estructura para los mismos.
    
    
    struct sema{
        int value; 
        int oc;
        struct spinlock semlock;
        };

    
Donde:

int value -> hace referencia al valor en el que esta el semáforo.

int oc -> hace referencia si el semáforo esta activo o no. 

struct spinlock semlock -> hace refería al lock del semáforo. 

Luego el programa de _*_pingpong_*_ fue implementado utilizando este sistema de semáforos, siguiendo la idea de procesos padres e hijos e intercalando entre la utilización de dos semaforos. 


<h3> Syscalls </h3>

_*_acquire():_*_ Verifica que el lock, del semáforo se encuentre disponible, para poder ser utilizado.

_*_release():_*_ Libera el lock del semáforo, utilizada siempre al final de cada syscall realizada por nosotros.

_*_sleep():_*_ Duerme al semáforo, durmiendo a su vez al proceos realizado por el mismo, utilizada en **sem_down** para dormir cuando el _value_ del semáforo es 0. 

_*_wakeup():_*_ Despierta al semáforo, volviendo a realizar el proceso que se hizo antes de que el semáforo haya sido puesto a dormir, utilizada en **sem_up** para despertar cuando el _value_ del semáforo es 0.

_*_argint():_*_ Nos permite leer un argumento de una _syscall_. Toma dos parametros, un **int** que nos dice que arguemento leer de la _syscall_, y un **int** donde se guardará ese argumento. Utilizada en **sysproc.c** para poder leer el id del semáforo, y en el caso puntual de **sys_up** el valor en el cual inicializaremos el semáforo.

<h3> Decisiones propías del grupo </h3>

Decidimos para la robustez de las llamadas al sistema, elaborar chequeos de casos en los cuales se _printea_ un error dando indicación en donde se encontro el fallo y porqué fallo, quedando así más limpio.  

Más allá de estos pequeños cambios insignificativos a la hora de correr el programa de forma correcta, no consideramos que hayamos hecho decisiones que ameriten una explicación a la hora de la implementación. 