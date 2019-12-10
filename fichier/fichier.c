#include <stdio.h>
#include "fichier.h"

Fichier ouvrir_fichier (Fichier fic, char * mode) {
  fic->f = NULL;
  fic->f = fopen (nomF,mode);
  return fic;
}

void ecrire_bit (Fichier fic, char bit) {
  fic->octet[iOctet++];
  if (fic->iOctet == 7) {

    fic->iOctet = 0;
  }
}

void ecrire_buffer (Fichier fic){
  int i;
  for (i = 0; i<fic->iOctet; i++) {
    fic->buffer[iBuffer]
  }
}

void ecrire_binaire (Fichier fic, char bit) {
  fwrite (&bit,1,1,fic);
  printf ("écriture de %c\n", bit);
}

char * lire_binaire (Fichier fic, int taille_buffer) {
  char buffer[taille_buffer];
  fread (buffer, sizeof(buffer[0]), sizeof(buffer), fic);
  return buffer;
  /*printf ("LIRE : %c\n", buffer[0]);
  printf ("LIRE : %c\n", buffer[1]);
  printf ("LIRE : %c\n", buffer[2]);
  printf ("LIRE : %c\n", buffer[3]);*/
}

void fermer_fichier (Fichier fic) {
  fclose(fic->f);
  printf("Fichier fermé\n");
}

bool fichier_existe(char* filename) {
	FILE* f = fopen(filename, "r");
	if (f == NULL) {
		return false;
	}
	fclose(f);
	return true;
}


/*
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
*/
