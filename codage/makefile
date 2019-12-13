CC = gcc
CCOPTS = -Wall

all: mon_exe

fichier.o: ../fichier/fichier.c ../fichier/fichier.h
	${CC} ${CCOPTS} -c fichier.c

arbre.o: ../arbre/arbre.c ../arbre/arbre.h
	${CC} ${CCOPTS} -c arbre.c

codage.o: codage.c
	${CC} ${CCOPTS} -c codage.c

mon_exe: codage.o ../fichier/fichier.o ../arbre/arbre.o
	${CC} ${CCOPTS} -o mon_exe codage.o ../fichier/fichier.o ../arbre/arbre.o

clean:rm *.o ; rm mon_exe
