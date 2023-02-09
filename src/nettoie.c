#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/sem.h>

#define TAILLE 1024

int main(){
    
    int addr, my_sem;

    addr = shmget((key_t)1234,TAILLE+sizeof(int),0600|IPC_CREAT);
    my_sem = semget(1234, 1, IPC_CREAT);

    if (addr<0) { perror("Error shmget"); exit(1); }

    if(semctl(my_sem, 1, IPC_RMID)<0){ perror("error semctl"); exit(1); }

    if (shmctl(addr, IPC_RMID, NULL)<0) { perror("Error shmctl"); exit(1); }


  
    return 0;
}