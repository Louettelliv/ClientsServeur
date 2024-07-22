/* ******************* *
* Fichier CL_lecteur.c *
*    Version finale    *
*       19/04/2023     *
*   CALDEIRA VILLETTE  *
* ******************** */

#include "CL_include"
#include "CL_sem.h"

typedef int SEMAPHORE;

/** LECTEUR **
* ENTREE: n_canal = voie, sem = id semaphore, canal = tube, pt = tableau de donnee dans la memoire
* SORTIE: lecture des donnees dans la memoire et envoi au redacteur
* RETOUR: neant
**/
void lecteur(int n_canal, SEMAPHORE sem, int canal[], BUF *pt)
{
    char donnee_tps[50];
    time_t timestamp;
    struct tm *local_time;

    time(&timestamp);
    local_time = localtime(&timestamp);

    close(canal[0]);
    donnee_tps[0]=0;

    while (1)
    {

        P(sem);
        sprintf(donnee_tps, "Donnee voie %d : %d le %s", n_canal, (pt+n_canal-1)->tampon[(pt+n_canal-1)->n], asctime(local_time)); /*recup donnees + date*/
        /*if(n_canal==1)
            printf("Lecteur 1 : %s\n", donnee_tps);
        else
            printf("Lecteur 2 : %s\n", donnee_tps);*/
        write(canal[1], donnee_tps, strlen(donnee_tps)+1); /*envoi par un pipe au redacteur*/
        donnee_tps[0]=0; /*remise a 0 de la chaine permettant de recuperer la donnee*/
    }
}
