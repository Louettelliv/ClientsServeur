/* ***************** *
*  Fichier CL_msg.c  *
*   Version finale   *
*      19/04/2023    *
*  CALDEIRA VILLETTE *
* ****************** */

#include "CL_include"

/** IDENTIFICATION DE LA MESSAGERIE **
* ENTREE: neant
* SORTIE: messagerie identifiee
* RETOUR: code erreur <0 ou identificateur de la messagerie
**/
int IdentificationMessagerie()
{
	key_t key;
	int  msgid;

	if (( key = ftok(CleServeur,C_Msg)) < 0 ) /*cle messagerie*/
	   return CLEerr;
	msgid = msgget(key,0666); /*identifiant messagerie*/
	if(msgid<0)
		printf("Messagerie inaccessible\n");
	else
		printf("Messagerie identifiee\n");
	return msgid;
}

/** RELACHE DE LA MESSAGERIE **
* ENTREE: msgid = identificateur de la messagerie, pid
* SORTIE: messagerie deconnectee
* RETOUR: neant
**/
void RelacheMessagerie(int msgid, int pid)
{
	dmsgbuf message;
	
	/*Envoi DECONNECT*/
	message.type=DECONNECT;
	sprintf(message.txt, "%d", pid);
	if(msgsnd(msgid, &message, strlen(message.txt)+1, 0)==-1)
		printf("Envoi du message DECONNECT impossible\n");
	else
		printf("Envoi du message DECONNECT reussi; Messagerie relachee\n");
}