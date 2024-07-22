/* ***************** *
*  Fichier CL_sem.h  *
*   Version finale   *
*      19/04/2023    *
*  CALDEIRA VILLETTE *
* ****************** */

typedef int SEMAPHORE;

key_t Creer_cle(char *nom_fichier);
SEMAPHORE Creer_sem(key_t key);
void Changer_sem(SEMAPHORE sem, int val);
void P(SEMAPHORE sem);
void V(SEMAPHORE sem);
void Detruire_sem(SEMAPHORE sem);