#include <stdio.h>
#include "fichier.h"

fichier ouvrir_fichier (char * nomF, char * mode) {
  fichier fic;
  fic = NULL;
  fic = fopen (nomF,mode);

  if (fic == NULL)
    printf("ERREUR : Fichier introuvable ou mode invalide\n");
  return fic;
}

void ecrire_binaire (fichier fic, char bit) {
  fwrite (&bit,1,1,fic);
  printf ("écriture de %c\n", bit);
}

void lire_binaire (fichier fic, int taille_buffer) {
  char buffer[taille_buffer];
  fread (buffer, sizeof(buffer[0]), sizeof(buffer), fic);

  printf ("LIRE : %c\n", buffer[0]);
  printf ("LIRE : %c\n", buffer[1]);
  printf ("LIRE : %c\n", buffer[2]);
  printf ("LIRE : %c\n", buffer[3]);
}

void fermer_fichier (fichier fic) {
  fclose(fic);
  printf("Fichier fermé\n");
}

void main () {
  fichier ficW = ouvrir_fichier("test.bin", "wb");
  ecrire_binaire (ficW, '1');
  ecrire_binaire (ficW, '0');
  ecrire_binaire (ficW, '1');
  fermer_fichier(ficW);

  fichier ficR = ouvrir_fichier("test.bin", "rb");
  lire_binaire (ficR, 10);
  fermer_fichier(ficR);
}
