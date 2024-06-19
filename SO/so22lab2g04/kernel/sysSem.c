#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "proc.h"
#include "fs.h"
#include "sleeplock.h"
#include "file.h"


#define MAX_sem 32

struct sema{
    int value;
    int oc;
    struct spinlock semlock;
};

struct sema array_sem[MAX_sem];

int 
sem_open(int sem, int value)
{
    if (value >= 0 && sem <= MAX_sem && array_sem[sem].oc == 0){
        acquire(&array_sem[sem].semlock);

        array_sem[sem].value=value;
        array_sem[sem].oc = 1;

        release(&array_sem[sem].semlock);
    }
    else {
        if(value < 0){
            printf("El valor debe ser un número natural.\n");
            exit(0);
        }
        if (sem > MAX_sem){
            printf("La cantidad de semaforos disponibles es %d.\n" , MAX_sem);
            exit(0);
        }
        if(array_sem[sem].oc != 0){
            printf("El semáforo se encuentra cerrado.\n");
            exit(0);
        }
    }


    return 0;
}

int
sem_up(int sem)
{
    if (array_sem[sem].oc == 1){
        acquire(&array_sem[sem].semlock);
        if (array_sem[sem].value == 0){
            wakeup(&array_sem[sem].value);
        }
        array_sem[sem].value++;
        release(&array_sem[sem].semlock);
    }
    else {
        printf("El semáforo se encuentra cerrado.\n",sem);
        exit(0);
    }
    return 0;
}

int
sem_down(int sem)
{
    if (array_sem[sem].oc == 1){
        acquire(&array_sem[sem].semlock);
        while(array_sem[sem].value == 0){
            sleep(&array_sem[sem].value,&array_sem[sem].semlock);
        }
        array_sem[sem].value --;   
        release(&array_sem[sem].semlock);
    }
    else {
        printf("El semáforo se encuentra cerrado.\n");
        exit(0);
    }
    return 0;
}

int
sem_close(int sem)
{
    if (array_sem[sem].oc == 1){
        acquire(&array_sem[sem].semlock);
        array_sem[sem].value =0;
        array_sem[sem].oc = 0;
        release(&array_sem[sem].semlock);
    }
    else {
        printf("El semáforo ya se encuentra cerrado.\n");
        exit(0);
    }
    return 0;
}
