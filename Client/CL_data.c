/* ***************** *
*  Fichier CL_data.c *
*   Version finale   *
*      19/04/2023    *
*  CALDEIRA VILLETTE *
* ****************** */

#include "CL_include"

int voie;

/** ATTENTE RECEPTION DONNEE **
* ENTREE: neant
* SORTIE: donnee recue sur voie 
* RETOUR: voie = numero de voie ou une donnee est recue
**/
int ReceptionDonnees()
{
	pause();
	return voie;
}

/** DONNEE RECU -> IDENTIFICATION DE LA VOIE **
* ENTREE: signum = type du signal (SIGUSR1||SIGUSR2)
* SORTIE: voie identifiee
* RETOUR: neant
**/
void Voie(int signum)
{
    if(signum==SIGUSR1)
    {
        /*printf("Voie 1 a lire\n");*/
	    voie=1;
    }
    else if(signum==SIGUSR2) 
    {
        /*printf("Voie 2 a lire\n");*/
        voie=2;
    }
    else 
    {
        printf("Signal recu inattendu\n");
    }
}

/** RECUPERATION DONNEE **
* ENTREE: *pt = pointeur sur le tableau de donnees
* SORTIE: affichage de la donnee recue
* RETOUR: neant
**/
int RecuperationDonnees(BUF*pt)
{
	printf("%d\n", (pt+voie-1)->tampon[(pt+voie-1)->n]);
	return (pt+voie-1)->tampon[(pt+voie-1)->n];
}
