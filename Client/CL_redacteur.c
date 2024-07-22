/* ********************* *
* Fichier CL_redacteur.c *
*     Version finale     *
*        19/04/2023      *
*    CALDEIRA VILLETTE   *
* ********************** */

#include "CL_include"
#include "CL_sem.h"

typedef int SEMAPHORE;

/** REDACTEUR **
* ENTREE: canal = voie, canalA = tube entre le lecteur et le redacteur, sem = id semaphore, canalB = tube entre le redacteur et le lecteur
* SORTIE: reception des donnees du lecteur  et envoi au driver
* RETOUR: neant
**/
void redacteur(int canal, int canalA[], SEMAPHORE sem, int canalB[])
{
    int cpt=0;
    char donnee_tps[50]="";
    char donnees[500]="";

    close(canalA[1]);
    close(canalB[0]);

    while (1)
    {
        read(canalA[0], donnee_tps, 50*sizeof(char)); /*recep donnees, lecture*/
        cpt++;
        strcat(donnees,donnee_tps);
        if(cpt==5)
        {
        	strcat(donnees,"\n");
            cpt=0;
            /*if(canal==1)
                printf("Redacteur 1 :\n%s", donnees);
            else
                printf("Redacteur 2 :\n%s", donnees);*/
            V(sem);
            write(canalB[1], donnees, strlen(donnees)+1); /*envoie de 5 donnees a la fois au driver*/
            P(sem);
            donnees[0] = 0; /*reinitialisation de la chaine*/
        }
    }
}
