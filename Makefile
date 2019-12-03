exo : main.o liste.o arbre.o file.o fileArbre.o
		gcc -o exo main.o liste.o arbre.o file.o fileArbre.o

main.o : main.c liste.h arbre.h fileArbre.h
		gcc -c main.c

liste.o : liste.c liste.h
		gcc -c liste.c

arbre.o : arbre.c liste.h file.h arbre.h fileArbre.h
		gcc -c arbre.c

file.o : file.c liste.h file.h arbre.h
		gcc -c file.c

fileArbre.o : fileArbre.c arbre.h fileArbre.h
		gcc -c fileArbre.c
