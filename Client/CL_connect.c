/* ******************* *
* Fichier CL_connect.c *
*    Version finale    *
*       19/04/2023     *
*   CALDEIRA VILLETTE  *
* ******************** */

#include "CL_include"

/** CONNEXION AU SERVEUR **
* ENTREE: msgid = identificateur de la messagerie, pid
* SORTIE: client connecte au serveur
* RETOUR: CleClient = cle d'acces
**/
char* ConnexionServeur(int msgid, int pid)
{
	int erreur;
	dmsgbuf message;
	char* CleClient;
	
	/*Envoi CONNECT*/
	message.type=CONNECT;
	sprintf(message.txt, "%d", pid);
	if(msgsnd(msgid, &message, strlen(message.txt)+1, 0)==-1)
		printf("Envoi du message CONNECT impossible\n");
	else
		printf("Envoi du message CONNECT reussi\n");
	
	/*Reception CleClient*/
	if ((erreur=msgrcv(msgid,&message,L_MSG,pid,0)) <0)
    {
		if (errno==EINTR)
			erreur=0;
		else
			printf("Clt:Erreur %d RecepMessage:%s %ld\n",errno,message.txt,message.type);
	}
	else
	{
		printf("Clt:Reception MESSAGE:%s %ld\n",message.txt,message.type);
		CleClient=(char*) malloc(L_MSG);
		strcpy(CleClient,message.txt);

		/*Envoi ACK : confirmation reception CleClient*/
		message.type=ACK;
		if(msgsnd(msgid, &message, strlen(message.txt)+1, 0)==-1)
			printf("Envoi du message ACK impossible\n");
		else
			printf("Envoi du message ACK reussi\n");
	}
	return CleClient;
}