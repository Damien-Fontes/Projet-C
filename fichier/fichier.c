#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

Fichier init_fichier (Fichier fic, char * nom) {
  fic.fic = NULL;
  fic.nom = nom;
  fic.iOctet = 0;
  fic.iBuffer = 0;


  return fic;
}

Fichier ouvrir_fichier (Fichier fic, char * mode) {
  fic.fic = NULL;
  fic.fic = fopen (fic.nom,mode);
  if (fic.fic != NULL)
    printf("Fichier ouvert\n");
  return fic;
}

void ecrire_bit (Fichier * fic, char bit) {
  fic->octet[fic->iOctet] = &bit;
  fic->iOctet++;

  printf("iOctet : %d\n", fic->iOctet);

  if (fic->iOctet == 7) {
    printf("Octet plein\n");
    ecrire_buffer (fic);
    fic->iOctet = 0;
  }
}

void ecrire_buffer (Fichier * fic){
  int i;
  for (i = 0; i<fic->iOctet; i++) {
    fic->buffer[fic->iBuffer++];
    printf("iBuffer : %d\n", fic->iBuffer);
    if (fic->iBuffer == sizeof (fic->buffer)) {
      ecrire_binaire (fic);
      fic->iBuffer = 0;
    }
  }
}

void ecrire_binaire (Fichier * fic) {
  fwrite (&fic->iBuffer,1,1,fic->fic);
}

void lire_binaire (Fichier fic, char * buffer) {
  fread (buffer, sizeof(buffer[0]), sizeof(buffer), fic.fic);
}

void verification_Fic (Fichier * fic) {
  if (fic->iOctet != 0) {
    ecrire_buffer (fic);
    fic->iOctet = 0;
    if (fic->iBuffer != 0) {
      ecrire_binaire (fic);
      fic->iBuffer = 0;
    }
  }
}

void fermer_fichier (Fichier * fic) {
  verification_Fic (fic);
  fclose(fic->fic);
  printf("Fichier fermé\n");
}

/*bool fichier_existe(char* filename) {
	FILE* f = fopen(filename, "r");
	if (f == NULL) {
		return false;
	}
	fclose(f);
	return true;
}*/



void main () {
  Fichier ficW;
  //ficW = (Fichier) malloc (sizeof(Fichier));
  ficW = init_fichier (ficW, "../test.txt");
  ficW = ouvrir_fichier(ficW, "w");
  Fichier * f = &ficW;
  ecrire_bit (f, '1');
  ecrire_bit (f, '0');
  ecrire_bit (f, '1');
  ecrire_bit (f, '1');
  ecrire_bit (f, '1');
  ecrire_bit (f, '0');
  ecrire_bit (f, '1');
  ecrire_bit (f, '1');
  fermer_fichier(f);

/*  fichier ficR = ouvrir_fichier("test.bin", "rb");
  lire_binaire (ficR, 10);
  fermer_fichier(ficR);*/
}
