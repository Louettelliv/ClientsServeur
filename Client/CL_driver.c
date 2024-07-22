/* ******************* *
*  Fichier CL_driver.c *
*    Version finale    *
*       19/04/2023     *
*   CALDEIRA VILLETTE  *
* ******************** */

#include "CL_include"

/** DRIVER **
* ENTREE: canal = tube entre le redacteur et le driver
* SORTIE: redirection de la sortie du pipe entre le redacteur et le driver vers le descripteur 0 + lancement du driver
* RETOUR: neant
**/
void driver(int canal[])
{
	close(0);
	dup(canal[0]);
	/*close(canal[0]);*/
	close(canal[1]);
	if(execlp("./Driver.exe", "./Driver.exe", NULL)<0) /* execution de './Driver.exe'*/
	{
		printf("erreur");
	}
    /*char donnees[500];

    close(canal[1]);
    while(1)
	{	
		read(canal[0],donnees,sizeof(donnees));
		printf("Driver: \n%s\n", donnees);
	}*/
}
