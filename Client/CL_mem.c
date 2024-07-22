/* ***************** *
*  Fichier CL_mem.c  *
*   Version finale   *
*      19/04/2023    *
*  CALDEIRA VILLETTE *
* ****************** */

#include "CL_include"

/** IDENTIFICATION DE LA MEMOIRE PARTAGEE **
* ENTREE: cleclient = cle d'acces
* SORTIE: memoire partagee identifiee
* RETOUR: code erreur <0 ou identificateur de la memoire partagee
**/
int IdentificationMemoire(char* cleclient)
{
	int CLTshmid;
	key_t key;

	if (( key = ftok(cleclient,C_Shm)) < 0 )
		return CLEerr;
	if ((CLTshmid = shmget(key,2*sizeof(BUF),0666|IPC_EXCL)) <0) /*Obtention de l'id*/
		return SHMerr;
	printf("Identification memoire reussie\n");
	return CLTshmid;
 }

/** ATTACHEMENT A LA MEMOIRE PARTAGEE **
* ENTREE: id = identifiant de la memoire partagee, **ptr = acces tableau de donnees
* SORTIE: memoire partagee attachee
* RETOUR: neant; 
**/
void AttacheMemoire(int id,BUF **ptr)
{
	BUF *MemTamponPtr;
	if ((MemTamponPtr = (BUF *)shmat(id,NULL,0)) == 0 )
		printf("Attachement de la memoire echoue\n");
	else
	{
		printf("Attachement de la memoire reussi\n");
		*ptr = MemTamponPtr ; 
	}
}
