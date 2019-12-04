#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "compression.h"
#include "../fichier/fichier.h"

#define ARG_SHORT       "-"
#define ARG_COMPRESS    "c"
#define ARG_DECOMPRESS  "e"

#define COMPRESS 1
#define DECOMPRESS -1
#define UNDEFINED 0

int main(int argc, char** argv) {

	int i, mode;
	char* nom_fichier;

	mode = UNDEFINED;
	// Lecture des arguments
	for (i = 1; i < argc; ++i) {
		if (strcmp(argv[k], ARG_SHORT ARG_COMPRESS) == 0
			&& mode == UNDEFINED) {
			mode = COMPRESS;
		}
		else if (strcmp(argv[k], ARG_SHORT ARG_DECOMPRESS) == 0
			&& mode == UNDEFINED) {
			mode = DECOMPRESS;
		}
		else if (argv[k][0] == ARG_SHORT) {
			perror("Invalid arguments");
			return EXIT_FAILURE;
		}
		else {
			// appel d'une fonction file_exists et indique si cet argument est un fichier qui existe
			if (!fichier_existe(argv[k])) {
				perror("File doesn't exist");
				return EXIT_FAILURE;
			}
			nom_fichier = argv[k];
		}
	}

	// Si aucun mode n'a été spécifié, on quitte le programme.
	if (mode == UNDEFINED) {
		perror("Missing arguments");
		return EXIT_FAILURE;
	}

	if (mode == COMPRESS) {
		if (compression(filename) == -1) {
			perror("Erreur compression");
			return EXIT_FAILURE;
		}
	}
	else {
		if (decompression(filename) == -1) {
			perror("Erreur compression");
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}