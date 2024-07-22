/* ***************** *
*  Fichier CL_main.c *
*   Version finale   *
*      19/04/2023    *
*  CALDEIRA VILLETTE *
* ****************** */

#include "CL_include"
#include "CL_msg.h"
#include "CL_connect.h"
#include "CL_mem.h"
#include "CL_data.h"
#include "CL_sem.h"
#include "CL_lecteur.h"
#include "CL_redacteur.h"
#include "CL_driver.h"

typedef int SEMAPHORE;

int main(int argc, char *argv[])
{
    int nbdata, MsgID, PereID=getpid(), IDmemoire, IDLect1, IDLect2, IDRedac1, IDRedac2, i, voie, DriverID, canal;
    char* CleClient;
    BUF	*Tptr;
    key_t cle_lect1,cle_lect2, cle_driv;
    SEMAPHORE lect1, lect2, driv;
    int canal1[2], canal2[2], canal_driver[2];

    signal(SIGUSR1, Voie);
	signal(SIGUSR2, Voie);
	
	if (argc < 2)
    {
      /*printf("Usage : sv_zz  <nombre de donnees>"); */
      printf("Erreur dans le passage des parametres pour sv_zz\n");
      exit(0);
    }
  
    nbdata=atoi(argv[1]);
    if (nbdata <= 0)
    {
      printf("Erreur dans la valeur du parametre de sv_zz\n");
      exit(0);
    }
    
    printf("\n******************************************\n");
	printf("!!! Lancement client (pendant %s s) !!!\n",argv[1]);
	printf("******************************************\n");

    /*Identification de la messagerie*/
    MsgID = IdentificationMessagerie();
	printf("Identificateur de la messagerie : %d\n", MsgID);

    /*Connexion au serveur & Recuperation de la cle client*/
    CleClient=ConnexionServeur(MsgID, PereID);
	printf("Cle client : %s\n", CleClient);

    /*Identification de la memoire partagee & Attachement*/
    IDmemoire=IdentificationMemoire(CleClient);
    printf("Identificateur de la memoire partagee : %d\n", IDmemoire);
	AttacheMemoire(IDmemoire, &Tptr);

    /*Creation semaphore*/
    cle_lect1 = Creer_cle("CL_main.c");
    lect1=Creer_sem(cle_lect1);

	cle_lect2 = Creer_cle("CL_sem.c");
    lect2=Creer_sem(cle_lect2);
    
    cle_driv = Creer_cle("Driver.c");
    driv=Creer_sem(cle_driv);
    /*Creation tube*/
    if(pipe(canal1)==-1) printf("Erreur creation canal1");
	if(pipe(canal2)==-1) printf("Erreur creation canal2");
	if(pipe(canal_driver)==-1) printf("Erreur creation canal_driver");

    if((DriverID = fork ())) /* code du pere*/
    {
        if(( IDLect1 = fork()) == -1)
        {
            printf("Fils lecteur 1 non cree\n");
            exit(0);
        }
        else if (IDLect1 == 0 )/*code du fils lecteur 1*/
        {
            canal=1;
            lecteur(canal, lect1, canal1, Tptr); /*lecture des donnees dans mem partagee et envoie au redacteur*/
        }
        else /*code du pere*/
        {
            if(( IDLect2 = fork()) == -1)
            {
                printf("Fils lecteur 2 non cree\n");
                exit(0);
            }
            else if (IDLect2 == 0 )/*code du fils lecteur 2*/
            {
                canal=2;
                lecteur(canal, lect2, canal2, Tptr); /*lecture des donnees dans mem partagee et envoie au redacteur*/
            }
            else /*code du pere*/
            {
   	   	if(( IDRedac1 = fork()) == -1)
		    {
		        printf("Fils redacteur 1 non cree\n");
		        exit(0);
		    }
		    else if (IDRedac1 == 0 ) /*code du fils redacteur 1*/
		    {
		    	canal =1;
		        redacteur(canal, canal1, driv, canal_driver); /*reception des donnees du lecteur et envoie au driver*/
		    }
		    else /*code du pere*/
		    {
		        if(( IDRedac2 = fork()) == -1)
		        {
		            printf("Fils redacteur 2 non cree\n");
		            exit(0);
		        }
		        else if (IDRedac2 == 0 ) /*code du fils redacteur 2*/
		        {
		        	canal=2;
		            redacteur(canal, canal2, driv, canal_driver); /*reception des donnees du lecteur et envoie au driver*/
		        }
		        else
		        {
		            for(i=0;i<nbdata;i++)
				{
				    voie=ReceptionDonnees(); /*Attente reception donnes du serveur*/
				    if(voie==1)
				        V(lect1);
				    else
				        V(lect2);
				}
				
                /*Arret processus fils*/
				kill(IDRedac1,SIGKILL);
				kill(IDRedac2,SIGKILL);
				kill(IDLect1,SIGKILL);
				kill(IDLect2,SIGKILL);
				kill(DriverID,SIGKILL);
		        }
		  }
            }
        }
    }
    else
    {
        driver(canal_driver); /*reception donnes redacteur et affichage*/
    }

    /*Destruction semaphore*/
    Detruire_sem(lect1);
    Detruire_sem(lect2);
    Detruire_sem(driv);

    /*Relache de la messagerie*/
    RelacheMessagerie(MsgID, PereID);

    /*Fin du processus pere*/
    return 0;
}