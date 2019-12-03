exec : main.o liste.o arbre.o
		gcc -o exo main.o liste.o arbre.o

main.o : main.c liste.h arbre.h
		gcc -c main.c

liste.o : liste.c liste.h
		gcc -c liste.c

arbre.o : arbre.c liste.h arbre.h
		gcc -c arbre.c
