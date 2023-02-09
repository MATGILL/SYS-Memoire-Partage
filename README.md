
# TP-Mémoire partagé
Compte-rendu





#### Exécutez le programme plusieurs fois de suite. Que fait ce programme?

 Le programme créé un tableau contenant des indice de processus qui utilise le segment de mémoire. Tant qu'on a pas supprimer le segment de mémoire
 le tableau gardera toujours les **pid** des processus précédent.

#### ► Pourquoi n’utilise-t-il pas le paramètre IPC_PRIVATE comme premier paramètre de shmget()?

Le paramètre **IPC_PRIVATE** sert a partagé le segment avec les processus enfant, ce n'est pas notre cas on préfère utiliser un point de rendez-vous (key).

#### ► Pourquoi le programme ne détruit-il pas le segment de mémoire partagée après avoir appellé shmdt()?

La commande **shmdt()** sert a détacher un segment et ne va pas le supprimer, on pourrait toujours s'y accrocher plus tard.
Il faut donc utiliser la commande : **shmctl()** avec le paramètre **IPC_RMID**.

#### ► Si vous appelez le programme plusieurs fois, combiende segments seront créés?

Si on l'appel n foix il va créé un seul segment, il sera le même pour tout les processus grace à la key (point de rendez-vous)

## Questions 1 :
#### le programme nettoie.c qui détruit le segment de mémoire partagé créé par tp3.C
```c
int main(){
    
    int addr, my_sem;
    //on récuprèe l'id du segment de mémoir partagé
    addr = shmget((key_t)1234,TAILLE+sizeof(int),0600|IPC_CREAT);
    
    //on récupère l'id de la sémaphore
    my_sem = semget(1234, 1, IPC_CREAT);

    if (addr<0) { perror("Error shmget"); exit(1); }

    if(semctl(my_sem, 1, IPC_RMID)<0){ perror("error semctl"); exit(1); }

    if (shmctl(addr, IPC_RMID, NULL)<0) { perror("Error shmctl"); exit(1); }
  
    return 0;
}
```


## Questions 2 :
#### ► Que se passe-t-il si vous lancez le programme tp3 plusieurs fois simultanément (dans des fenêtres différentes)?

Le programme ne réalisera pas ce que l'on veut et affichera un message illisible, car les deux processus tenteront de réaliser la même chose 
au même moment. D'où l'utilité des *race-condition*.


## Auteurs

- [Mathis GILLARD](https://github.com/MATGILL)
- [Raphaël HURBAIN](https://github.com/WizMxn)

