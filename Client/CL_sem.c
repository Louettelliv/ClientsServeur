/* ***************** *
*  Fichier CL_sem.c  *
*   Version finale   *
*      19/04/2023    *
*  CALDEIRA VILLETTE *
* ****************** */

#include "CL_include"

typedef int SEMAPHORE;

/** CREATION D'UNE CLEE **
* ENTREE: nom de fichier
* SORTIE: clee cree
* RETOUR: cle
**/
key_t Creer_cle(char *nom_fichier)
{
  key_t cle;

  if ( (cle = ftok(nom_fichier,'0')) == -1)
    {
      perror("Creer_cle");
      exit(EXIT_FAILURE);
    }
  return cle;
}

/** CREATION D'UN SEMAPHORE **
* ENTREE: cle
* SORTIE: semaphore cree cree
* RETOUR: sem = identifiant du semaphore
**/
 SEMAPHORE Creer_sem(key_t key)
{
  SEMAPHORE sem;
  int r;
  int nombre_de_sem=1;
  int val_init=0;
  sem = semget(key, nombre_de_sem,IPC_CREAT|IPC_EXCL|0666);
  if (sem < 0)
    {
      perror("Creer_sem : semget");
      exit(EXIT_FAILURE);
    }
  r = semctl(sem,nombre_de_sem-1,SETVAL,val_init);
  if (r <0)
    {
      perror("Creer_sem : semctl");
      exit(EXIT_FAILURE);
    }
  return sem;
}

/** MODIFICATION VALEUR SEMAPHORE **
* ENTREE: sem = identifiant du semaphore, val
* SORTIE: valeur semaphore changee
* RETOUR: neant
**/
void Changer_sem(SEMAPHORE sem, int val)
{
  struct sembuf sb[1];
  int nombre_de_sem=1;

  sb[0].sem_num = nombre_de_sem-1;
  sb[0].sem_op = val;
  sb[0].sem_flg=0;

  if (semop(sem,sb,nombre_de_sem) != 0)
    {
	perror("Changer_sem");
	exit(EXIT_FAILURE);
    }
}

/** PRISE DE LA RESSOURCE **
* ENTREE: sem = identifiant du semaphore
* SORTIE: valeur semaphore mise a -1
* RETOUR: neant
**/
void P(SEMAPHORE sem)
{
  Changer_sem(sem,-1);
}

/** REMISE DE LA RESSOURCE **
* ENTREE: sem = identifiant du semaphore
* SORTIE: valeur semaphore mise a 1
* RETOUR: neant
**/
void V(SEMAPHORE sem)
{
  Changer_sem(sem,1);
}

/** DESTRUCTION SEMAPHORE **
* ENTREE: sem = identifiant du semaphore
* SORTIE: semaphore detruit
* RETOUR: neant
**/
void Detruire_sem(SEMAPHORE sem)
{
    int nombre_de_sem=1;
    if (semctl(sem,nombre_de_sem-1,IPC_RMID,0) != 0)
      {
	perror("Detruire_sem");
	exit(EXIT_FAILURE);
      }
}