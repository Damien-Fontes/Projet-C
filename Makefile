projet : main.o fichier/fichier.o arbre/arbre.o codage/codage.o compression/compression.o
	gcc -o projet main.o fichier.o arbre.o codage.o compression.o

main.o : main.c fichier/fichier.h compression/compression.h
	gcc -c main.c

fichier/fichier.o : fichier/fichier.c fichier/fichier.h
	gcc -c fichier/fichier.c

arbre/arbre.o : arbre/arbre.c arbre/arbre.h
	gcc -c arbre/arbre.c

codage/codage.o : codage/codage.c arbre/arbre.h fichier/fichier.h codage/codage.h
	gcc -c codage/codage.c

compression/compression.o : compression/compression.c arbre/arbre.h codage/codage.h fichier/fichier.h compression/compression.h
	gcc -c compression/compression.c

clean:
	rm *.o ; rm main
