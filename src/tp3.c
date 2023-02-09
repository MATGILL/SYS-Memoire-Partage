#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/sem.h>

#define TAILLE 1024

void ecrire_tableau(int *compteur, char *tableau) {
  char message[64], *msg=message;
  snprintf(message, 64, "Je suis le processus %d!\n", getpid());

  while ((*compteur<TAILLE)&&(*msg)) {
    tableau[*compteur] = *msg;
    msg++;
    usleep(100000);
    (*compteur)++;
  }
}

int main() {
  
  struct sembuf up = {0, 1, 0};
  struct sembuf down = {0, -1, 0};
  int my_sem;
  int id, *compteur;
  char *tableau;



  id = shmget((key_t)1234,TAILLE+sizeof(int),0600|IPC_CREAT);
  if (id<0) { 
   perror("Error shmget"); 
   exit(1); 
  }

  // créetion d'un tableau de sémaphores
  my_sem = semget((key_t)1234, 1, 0600);
  //si la sém n'existe pas
  if(my_sem <0){
    //création de la sémaphore
    my_sem = semget((key_t)1234, 1, 0600 | IPC_CREAT);
    if(my_sem < 0){
      perror("error semget"); 
      exit(1);
    }
    if(semctl(my_sem, 0,SETVAL, 1)<0){
      perror("error setval to 1");
      exit(1);
    }

  }
   
   //on entre dans la section critique (on en sort aux up())
  semop(my_sem, &down, 1); //DOWN()

  compteur = (int*) shmat(id,0,0);
  if (compteur==NULL) { 
    perror("Error shmat"); 
    semop(my_sem, &up, 1); //UP()
    exit(1); 
  }

  tableau = (char *)(compteur + 1);
  
  ecrire_tableau(compteur, tableau);
  printf("%s\n", tableau);

  if (shmdt(compteur)<0) { 
    perror("Error shmdt");
    semop(my_sem, &up, 1); //UP()
    exit(1); 
  }

  semop(my_sem, &up, 1);
  return 0;
}


