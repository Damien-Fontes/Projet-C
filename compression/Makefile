arbredir = ../arbre/
codagedir = ../codage/
fichierdir = ../fichier/

CC = gcc
CFLAGS = -std=c11 -Wall -Wconversion -Werror -Wextra -Wpedantic -I$(arbredir) -I$(codagedir) -I$(fichierdir)
LDFLAGS =
VPATH = $(arbredir) $(codagedir) $(fichierdir)
objects = main.o $(arbredir)arbre.o $(codagedir)codage.o $(fichierdir)fichier.o compression.o
executable = compression

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

$(arbredir)arbre.o: arbre.c arbre.h
$(codagedir)codage.o: codage.c codage.h
$(fichierdir)fichier.o: fichier.c fichier.h
compression.o: compression.c compression.h arbre.h codage.h fichier.h
main.o: main.c arbre.h codage.h fichier.h compression.h