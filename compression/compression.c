#include <stdio.h>
#include <string.h>
#include "../arbre/arbre.h"
#include "../codage/codage.h"
#include "../fichier/fichier.h"
#include "compression.h"

int compression (char * name) {
  int tailleFichier, i;
  Fichier * fic;
  fic = creer_fichier(name, "r");

  tailleFichier = 0;
  while(feof(fic->fic) == 0) {
    lire_fic(fic);
    tailleFichier++;
  }
  fermer_fichier(fic, "r");


  char text[tailleFichier];
  text[tailleFichier] = '\0';
  fic = creer_fichier(name, "r");
  for (i = 0; i<tailleFichier; i++) {
    text[i] = lire_fic(fic);
  }
  fermer_fichier(fic, "r");

  calcul_frequences (text);
  calcul_arbre_codage();
  print_arbre(arbre_codage);

  char encodage[256]
  tableau_encodage(arbre_codage, 0, encodage);

  return 0;
}
