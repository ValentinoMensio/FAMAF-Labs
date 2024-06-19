#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void
main(int argc, char *argv[])
{
  sem_open(0, 1); //father
  sem_open(1, 0); //child

  int N = atoi(argv[1]);
  int pid=fork();

  if(pid>0){
    int childstatus;
    for(int i=0; i<N; i++){
      sem_down(0);
      printf("Ping \n");
      sem_up(1);
    }
    wait(&childstatus);
  }else{
    for(int i=0; i<N; i++){
      sem_down(1);
      printf("Pong \n");
      sem_up(0);
    }
    exit(0);
  }

  sem_close(0);
  sem_close(1);
}