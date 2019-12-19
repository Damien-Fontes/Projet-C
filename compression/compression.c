#include <stdio.h>
#include <string.h>
#include "codage.h"
#include "fichier.h"
#include "compression.h"

int compression (char * name) {
  int tailleFichier;
  Fichier * fic;
  fic = creer_fichier(fic, name, "r");

  tailleFichier = 0;
  while(feof(fic->fic) == 0) {
    taillleFichier++;
  }
  fermer_fichier(fic, "r");

  char text[tailleFichier];
  fic = creer_fichier(fic, name, "r");
  while(feof(fic->fic) == 0) {
    strcat(text, lire_fic(fic));
  }
  fermer_fichier(fic, "r");

  printf("%s\n", text);

  return 0;
}
