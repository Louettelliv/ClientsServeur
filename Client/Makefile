######################
#  Fichier Makefile  #
#   Version finale   #
#      19/04/2023    #
#  CALDEIRA VILLETTE #
######################

CC = gcc
CFLAGS = -Wall -ansi -D _GNU_SOURCE 
CFLAG2 = -c -Wall -ansi -D _GNU_SOURCE 
OBJETS = CL_main.o CL_msg.o CL_connect.o CL_mem.o CL_data.o CL_sem.o CL_lecteur.o CL_redacteur.o CL_driver.o
EXE=CL

$(EXE): $(OBJETS) 
	$(CC) $(CFLAGS) $(OBJETS) -o $(EXE)

CL_main.o : CL_main.c CL_include
	$(CC) $(CFLAG2) CL_main.c -o CL_main.o

CL_msg.o : CL_msg.c CL_include CL_msg.h
	$(CC) $(CFLAG2) CL_msg.c -o CL_msg.o
	
CL_connect.o : CL_connect.c CL_include CL_connect.h
	$(CC) $(CFLAG2) CL_connect.c -o CL_connect.o
	
CL_mem.o : CL_mem.c CL_include CL_mem.h
	$(CC) $(CFLAG2) CL_mem.c -o CL_mem.o

CL_data.o : CL_data.c CL_include CL_data.h
	$(CC) $(CFLAG2) CL_data.c -o CL_data.o

CL_sem.o : CL_sem.c CL_include CL_sem.h
	$(CC) $(CFLAG2) CL_sem.c -o CL_sem.o

CL_lecteur.o : CL_lecteur.c CL_include CL_lecteur.h
	$(CC) $(CFLAG2) CL_lecteur.c -o CL_lecteur.o

CL_redacteur.o : CL_redacteur.c CL_include CL_redacteur.h
	$(CC) $(CFLAG2) CL_redacteur.c -o CL_redacteur.o

CL_driver.o : CL_driver.c CL_include CL_driver.h
	$(CC) $(CFLAG2) CL_driver.c -o CL_driver.o

clean:
	@rm -f *~ *.o $(EXE)