# Laboratorio 3 

------



- **Pintos, Mauricio**
- **Mensio, Valentino**
- **Martinez, Tomas**



------

## Primera Parte: Estudiando el planificador de xv6

### Pregunta 1:

Analizar el código del planificador y responda: ¿Qué política de planificación utiliza xv6 para elegir el próximo proceso a ejecutarse? 

*Pista: xv6 nunca sale de la función scheduler por medios “normales”.*

### Respuesta: 

 Leyendo **xv6** podemos encontrar que la politica de planificacion que maneja es de **Round Robin**, donde se permite la ejecucion de procesos en simultaneo, aquellos que esten disponibles para ejecutar (marcados con RUNNABLE), con un "tiempo" llamado **quantum**. 

En **xv6** es muy particular pues se tiene un array o tabla con una cantidad determinada de procesos, denominada por la variable NPROC, (esta misma determina que el maximo de procesos es de 64) y se va fijando siempre llamando a scheduler.

### Pregunta 2:

Analizar el código que interrumpe a un proceso al final de su quantum y responda: 

1.  ¿Cuánto dura un quantum en xv6?
2.  ¿Cuánto dura un cambio de contexto en xv6?
3.  ¿El cambio de contexto consume tiempo de un quantum?
4.  ¿Hay alguna forma de que a un proceso se le asigne menos tiempo?

### Respuestas: 

1. Analizando codigos como el mismo start.c, tampoline.S, switch.S, trap.c entre otros, vemos que cuando hay una interrupcion, el kernel toma el control, entonces ese tiempo que hay entre cada interrupcion va ser lo mismo que el quantum. Por lo tanto si nos fijamos en start.c, el tiempo en el que se inicializa en timer es de: int interval = [1000000](https://bitbucket.org/sistop-famaf/so22lab3g04/commits/1000000);
2. El cambio de contexto solo ocurre cuando el proceso ya está en modo kernel, y todos sucede de la misma forma, cada vez que el contexto xv6 cambia a Scheduler() función en proc.c, puede suponer que este cambio de contexto es corto, dura como el cambio de registros.
3. De hecho el cambio de contexto si consume parte del quantum pues cada tick tiene una cantidad de tiempo dada o determinada por el reloj del hardware.
4. Siempre en xv6 el quantum va ser el mismo, es decir nunca se le asigna mas o menos tiempo a un programa, si puede ocurrir que un proceso termine antes de que se le acabe el quatum, entonces se va a elegir a otro proceso para trabajar hasta que el quantum del primer proceso acabe. Pero sin embargo una forma de cambiar su quantum puede ser aumentando la cantidad de ticks de un procesos determinado  



------



## Segunda Parte: Cómo el planificador afecta a los procesos



### Quantum Default con el planificador de xv6: RR



![](https://bitbucket.org/sistop-famaf/so22lab3g04/raw/7ccc292d695830ad080f42185b7aafca9e1b7df4/imagenes/quantum%20default.png)



Caso 0: Vemos que cuando un IOBench trabaja solo, el promedio de I/O operations por cada tick en 5 minutos es de  54,0377.

Caso 1: Vemos que cuando un CPUBench trabaja solo, el promedio de las KLFO por cada tick en 5 minutos es de 52,585. Traduciendo este numero a un número neto de operaciones serían aproximadamente 52585 operaciones por tick.

Caso 2: Vemos que cuando se ejecutan los dos benchmarks en paralelo ocurren diferentes cosas. El planificador default de xv6(**RR**) va a favorecer más al CPUBench, este es llamado 27 veces a diferencia del IOBench que es llamado solo 15 veces. Por otra parte, el promedio de las KLFO del CPUBench por cada tick en 5 minutos es de 55,2382 (*aproximadamente 55238,2 operaciones por tick*) y el promedio de I/O operations por cada tick en 5 minutos es de 0,328. 

Caso 3: Vemos que cuando ejecutamos dos benchmarks de misma naturaleza, en este caso dos IOBenchs, estos se van alternando entre ellos. Se podría decir que tienen una misma prioridad y que ambos se ejecutaran una misma cantidad de veces. El promedio de las I/O operations por cada tick en 5 minutos del primer IOBench es de 51,025. Mientras que el promedio de las I/O operations por cada tick en 5 minutos del segundo IOBench es de 51,212. 

Caso 4:Lo mismo ocurre cuando ejecutamos dos CPUBenchs. Se ejecutan una misma cantidad de veces y su promedio varía muy poco entre ellos. El promedio de las KLFO por cada tick en 5 minutos del primer CPUBench es de 56,485 (*aproximadamente 56485 operaciones por tick*) y el promedio de las KLFO por cada tick en 5 minutos del segundo CPUBench es de 57,129 (*aproximadamente 57129 operaciones por tick*).



### Quantum x10 veces más chico con el planificador de xv6: RR 



![](https://bitbucket.org/sistop-famaf/so22lab3g04/raw/7ccc292d695830ad080f42185b7aafca9e1b7df4/imagenes/quantum%20x10%20veces%20m%C3%A1s%20chico.png)

Podemos observar cuando el quantum es 10 veces más chico que el cambio más notable es a la hora de correr los benchmarks del cpu. Se puede ver una caida considerable en la cantidad de operaciones que es capaz de realizar el CPUBench, a diferencia de cuando el quantum tenia su magnitud default. Por su lado la cantidad de operaciones de IOBench fluctua pero no lo suficiente como para llamar la atención.

Caso 0: Promedio de I/O operations por cada tick en 5 minutos es de 54,2546.

Caso 1: Promedio de las KLFO por cada tick en 5 minutos es de 5,5907 (*aproximadamente 55907 operaciones por tick*).

Caso 2: Promedio de las I/O operations por cada tick en 5 minutos es de 3,3133. Promedio de las KLFO por cada tick en 5 minutos es de 5,185 (*aproximadamente 51850 operaciones por tick*).

Caso 3: Promedio de las I/O operations (1) por cada tick en 5 minutos es de 51,692. Promedio de las I/O operations (2) por cada tick en 5 minutos es de 52,362.

Caso 4: Promedio de las KLFO (1) por cada tick en 5 minutos es de 6,806 (*aproximadamente 68060 operaciones por tick*). Promedio de las KLFO (2) por cada tick en 5 minutos es de 6,7508 (*aproximadamente 67508 operaciones por tick*). 

### Quantum x100 veces más chico con el planificador de xv6: RR



![](https://bitbucket.org/sistop-famaf/so22lab3g04/raw/7ccc292d695830ad080f42185b7aafca9e1b7df4/imagenes/quantum%20x100%20veces%20m%C3%A1s%20chico.png)

En este caso igual podemos observar realmente que el benchmark de la cpu es el que mas se ve afectado hacia este cambio. Las operaciones vuelven a caer aún más haciendo aún más notable el cambio. Por su parte el IOBench se mantiene estable y sin cambios importantes.

Caso 0: Promedio de I/O operations por cada tick en 5 minutos es de 46,1356.

Caso 1: Promedio de las KLFO por cada tick en 5 minutos es de 0,4352 (*aproximadamente 4352 operaciones por tick*).

Caso 2: Promedio de las I/O operations por cada tick en 5 minutos es de 27,0535. Promedio de las KLFO por cada tick en 5 minutos es de 0,1889 (*aproximadamente 1889 operaciones por tick*).

Caso 3: Promedio de las I/O operations (1) por cada tick en 5 minutos es de 58,6251. Promedio de las I/O operations (2) por cada tick en 5 minutos es de 58,8151.

Caso 4: Promedio de las KLFO (1) por cada tick en 5 minutos es de 0,5677 (*aproximadamente 5677 operaciones por tick*). Promedio de las KLFO (2) por cada tick en 5 minutos es de 0,5303 (*aproximadamente 5303 operaciones por tick*). 


------



## Tercera Parte: Rastreando la prioridad de los procesos

Habiendo visto las propiedades del planificador existente, lo reemplazar con un planificador **MLFQ** de tres niveles. A esto se debe hacer de manera gradual, primero rastrear la prioridad de los procesos, sin que esto afecte la planificación.

1. Agregue un campo en struct proc que guarde la prioridad del proceso (entre 0 y NPRIO-1 para #define **NPRIO** 3 niveles en total) y manténgala actualizada según el comportamiento del proceso, además agregue un campo en struct proc que guarde la cantidad de veces que fue elegido ese proceso por el planificador para ejecutarse y se mantenga actualizado:
   - **MLFQ** regla 3: Cuando un proceso se inicia, su prioridad será máxima. 
   - **MLFQ** regla 4: Descender de prioridad cada vez que el proceso pasa todo un quantum realizando cómputo. 
   - Ascender de prioridad cada vez que el proceso se bloquea antes de terminar su quantum. *Nota: Este comportamiento es distinto al del **MLFQ** del libro.*

2. Para comprobar que estos cambios se hicieron correctamente, modifique la función procdump (que se invoca con CTRL-P) para que imprima la prioridad de los procesos y la cantidad de veces que fue elegido ese proceso por el planificador. Así, al correr nuevamente iobench y cpubench, debería darse que cpubench tenga baja prioridad mientras que iobench tenga alta prioridad.

### Respuestas:

Lo primero que realizamos fue definir **NPRIO**.

```c
#define NPRIO 3
```

Donde **NPRIO - 1** es la *prioridad minima*, y 0 es la *prioridad maxima*.

1. 

```c#
struct proc {
    ...
    uint prio; // Priority
    uint times_choseen // Times chosen by the planificator
    ...
}
```



Dentro de la estructura de los procesos, agregamos dos variables nuevas de tipo **unsigned int** que nos sirven para lo pedido en el inciso 1, guardar la prioridad del proceso y guardar la cantidad de veces que fue elegido el proceso por el planificador. 

- **MLFQ** regla 3: Lo solucionamos inicializando en **allocproc()**, que el proceso comience siempre con la mayor prioridad posible.
- **MLFQ** regla 4: Lo solucionamos en **yield()**, bajando su prioridad.
- Lo solucionamos en **sleep()**, ya que el proceso no termina, pasa de un estado de **RUNNING** a **SLEEPING**, considerandolo mas bien "bloqueado". 

2. 

```c
void
procdump(void)
{
    ...
    printf("%d %d %d %s %s", p->pid, p->prio, p->times_chosen, state, p->name);
    ...
}
```



------



## Cuarta Parte: Implementando MLFQ

### Quantum Default con el planificador: MLFQ

### Quantum x10 veces más chico con el planificador: MLFQ

### Quantum x100 veces más chico con el planificador: MLFQ
