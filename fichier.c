#include <stdio.h>
#include "fichier.h"

fichier ouvrir_fichier (char * nomF, char mode) {
  fichier fic;
  fic = NULL;
  fic = fopen (nomF,mode);
  if (fic == NULL)
    printf("ERREUR : Fichier introuvable ou mode invalide\n");
  return fic;
}

void ecrire_binaire (fichier fic, int bit) {
  fwrite ()
}

void fermer_fichier (fichier fic) {
  fclose(fic);
  printf("Fichier fermé\n");
}
