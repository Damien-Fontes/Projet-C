#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "fichier/fichier.h"
#include "compression/compression.h"

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
		if (strcmp(argv[i], ARG_SHORT ARG_COMPRESS) == 0
			&& mode == UNDEFINED) {
			mode = COMPRESS;
		}
		else if (strcmp(argv[i], ARG_SHORT ARG_DECOMPRESS) == 0
			&& mode == UNDEFINED) {
			mode = DECOMPRESS;
		}
		// else if (*argv[i][0] == ARG_SHORT) {
		// 	perror("Invalid arguments");
		// 	return EXIT_FAILURE;
		// }
		else {
			// appel d'une fonction file_exists et indique si cet argument est un fichier qui existe
			// if (!fichier_existe(argv[i])) {
			// 	perror("File doesn't exist");
			// 	return EXIT_FAILURE;
			// }
			nom_fichier = argv[i];
		}
	}

	// Si aucun mode n'a �t� sp�cifi�, on quitte le programme.
	if (mode == UNDEFINED) {
		perror("Missing arguments");
		return EXIT_FAILURE;
	}

	if (mode == COMPRESS) {
		if (compression(nom_fichier) == -1) {
			perror("Erreur compression");
			return EXIT_FAILURE;
		}
	}
	else {
		// if (decompression(nom_fichier) == -1) {
		// 	perror("Erreur compression");
		// 	return EXIT_FAILURE;
		// }
	}

	return EXIT_SUCCESS;
}
