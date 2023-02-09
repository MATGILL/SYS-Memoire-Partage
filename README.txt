Mathis GILLATD
Raphaël HURBAIN
INFO 2.1

===============================
Compte rendu TP-Mémoire partagé
================================

 ► Exécutez le programme plusieurs fois de suite. Que fait ce programme?
 Le programme créer un processus et affiche l'id de chacun des processus créé par se programme

 
 ►Pourquoi n’utilise-t-il pas le paramètre IPC_PRIVATE comme premier paramètre de shmget()?
Le paramètre IPC_PRIVATE sert a partagé le segment avec les processus enfant, ce n'est pas notre cas on préfère utiliser un point de rendez-vous.


► Pourquoi le programme ne détruit-il pas le segment de mémoire partagée après avoir appellé shmdt()? 
La commande shmdt() sert a détacher un segment et ne va pas le supprimer, on pourrait plus tard s'y raccrocher.
Il faut utiliser la commande : shmctl() avec le paramètre IPC_RMID

► Si vous appelez le programme plusieurs fois, combiende segments seront créés?
Si on l'appel n foix il va créé un seul segment, il sera le même pour tout les processus grace à la key (point de rendez-vous)


Question 2: 
-----------
Que se passe-t-il si vous lancez le programme tp3 plusieurs fois simultanément (dans des fenêtres différentes)?
Le programme ne réalisera pas ce que l'on veut et affichera un message illisible, car les deux processus tenteront de réaliser la même chose 
au même moment. D'où l'utilité des race-condition.

