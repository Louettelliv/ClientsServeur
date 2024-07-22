# Projet Unix
## CALDEIRA Quentin et VILLETTE Lou-Anne

### Introduction
Ce projet a pour but de faire communiquer un serveur et un client. Le Serveur écrit des données dans une mémoire partagée, et le Client vient lire ces données, grâce à un driver.

### État d'avancement
Le projet est arrivé à sa finalité, c'est-à-dire :
- Le Client fonctionne en lui indiquant un temps de fonctionnement donné
- L'accès à la messagerie et la mémoire partagée est fonctionnel
- Le driver permettant l'affichage des données est fonctionnel
- Le séquencement des lectures avec sémaphores est fonctionnel

### Description des différents fichiers
- **CL_msg** permet de récupérer l'identifiant de la messagerie et s'y connecter
- **CL_connect** permet de se connecter à la messagerie du serveur et de récupérer la *CleClient*
- **CL_mem** permet de récupérer l'identifiant de la mémoire partagée et de s'y attacher
- **CL_data** permet de récupérer les données envoyer par le serveur sur la réception du SIGNAL
- **CL_lecteur** permet de lire la donnée du serveur, et la transmet avec la date associée à un rédacteur via un pipe
- **CL_redacteur** permet de récupérer la données sortante du pipe et la transmet au driver
- **CL_driver** permet de faire l'affichage des données. Pour cela, la sortie du pipe est redirigée vers le descripteur 0. Ensuite, un `scanf` permettra de stocker dans une chaîne de caractère la redirection pour l'affichée
- **CL_sem** contient toutes les fonctions nécessaires à la manipulation des sémaphores (création, destruction, P, V...)

### Remarques
Après `ps -x`, aucun processus ne persiste à la fin de l'exécution du programme. De plus, après `ipcs`, aucun sémaphore ne persiste à la fin de l’exécution du programme.

### Excecution du programme
Pour exécuter le programme, il faut d'abord :
- Compiler le fichier `Driver.c`, et appeler son exécutable `Driver.exe` (normalement le fichier .exe est fourni). La ligne de commande est la suivante : `gcc -Wall -Ansi Driver.c -o Driver.exe`
- Compiler si besoin le Client avec `make clean` puis `make` dans le dossier CL
- Compiler si besoin le Serveur avec `make clean` puis `make` dans le dossier SV
- Executer **d'abord** le serveur avec `./SV <temps en secondes>` dans le dossier SV
- Executer **ensuite, dans un second terminal** le client avec `./CL <temps en secondes>` dans le dossier CL

