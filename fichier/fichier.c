#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

void init_fichier (Fichier *fic, char * nom) {
  fic->fic = NULL;
  fic->nom = nom;
  fic->iOctet = 0;
  fic->iBuffer = 0;
  fic->nbOctet = 0;
}

void free_fichier (Fichier *fic) {
  free (fic);
}

void ouvrir_fichier (Fichier *fic, char * mode) {
  fic->fic = NULL;
  fic->fic = fopen (fic->nom,mode);
  //if (fic->fic != NULL)
    printf("%s : Fichier ouvert. Mode : %s\n", fic->nom, mode);
}

void ecrire_bit (Fichier * fic, char bit) {
  fic->octet[fic->iOctet++] = bit;
  printf("Octet[%d] : %s, char : %c\n", fic->iOctet-1, &fic->octet[fic->iOctet-1], bit);

  if (fic->iOctet == 8) {
    ecrire_buffer (fic);
    fic->iOctet = 0;
  }
}

void ecrire_buffer (Fichier * fic){
  int i;
  unsigned char b, octet;
  b = 0x80;
  octet = 0;

  for (i = 0; i < 8; i++) {
    if (fic->octet[i] == '1')
      octet = octet | b;
    b = b >> 1;
  }

  fic->buffer[fic->iBuffer++] = octet;
  fic->nbOctet++;

  if (fic->iBuffer == sizeof (fic->buffer)) {
    ecrire_binaire (fic);
    fic->iBuffer = 0;
  }
}

void ecrire_binaire (Fichier * fic) {
  fwrite (&fic->buffer,1,fic->nbOctet,fic->fic);
  printf("Ecriture dans le fichier.\n" );
  printf("Buffer : %s\n",fic->buffer);
}

void verification_buffer (Fichier * fic) {
  if (fic->iOctet != 0) {
    ecrire_buffer (fic);
    fic->iOctet = 0;
  }
  if (fic->iBuffer != 0) {
    ecrire_binaire (fic);
    fic->iBuffer = 0;
  }
}

void fermer_fichier (Fichier * fic) {
  verification_buffer (fic);
  fclose(fic->fic);
  printf("Fichier fermé\n");
}

char lire_binaire (Fichier *fic) {
  int i;
  char bit;
  unsigned char d;
  d = 0x80;

  if (fic->nbOctetLu == 0) {
    fic->nbOctetLu = fread (fic->buffer, 1, sizeof(fic->buffer), fic->fic);

    fic->iBuffer = 0;
    fic->iOctet = 0;
    for (i = 0; i<8; i++) {
      if (fic->buffer[fic->iBuffer] == 1)
        fic->octet[i] = fic->buffer[fic->iBuffer]&d;
      d = d >> 1;
    }
    //fic->octet = fic->buffer[fic->iBuffer++];
    fic->nbOctet = fic->nbOctet + fic->nbOctetLu;
  }

  bit = fic->octet[fic->iOctet++];
  if (fic->iOctet == 8) {
    for (i = 0; i<8; i++) {
      if (fic->buffer[fic->iBuffer] == 1)
        fic->octet[i] = fic->buffer[fic->iBuffer]&d;
      d = d >> 1;
    }
    //fic->octet = fic->buffer[fic->iBuffer++];
    fic->iOctet = 0;

    if (fic->iBuffer == BLOCK_SIZE)
      fic->nbOctetLu = 0;
  }
  return bit;
}

void main () {
  Fichier * f;
  f = (Fichier*) malloc (sizeof(Fichier));
  init_fichier (f, "../test.bin");
  ouvrir_fichier(f, "wb");

/*  ecrire_bit (f, '1');
  ecrire_bit (f, '0');
  ecrire_bit (f, '1');
  ecrire_bit (f, '1');
  ecrire_bit (f, '1');*/
  ecrire_bit (f, '0');
  ecrire_bit (f, '1');
  ecrire_bit (f, 'a');
  ecrire_bit (f, 'b');
  ecrire_bit (f, 'c');
  ecrire_bit (f, 'd');
  ecrire_bit (f, 'e');
  ecrire_bit (f, 'f');
  ecrire_bit (f, 'g');
  ecrire_bit (f, 'h');
  ecrire_bit (f, 'i');
  fermer_fichier(f);

  ouvrir_fichier(f,"rb");
  printf ("Caractère lu : %c\n", lire_binaire(f));
  printf ("Caractère lu : %c\n", lire_binaire(f));
  printf ("Caractère lu : %c\n", lire_binaire(f));
  printf ("Caractère lu : %c\n", lire_binaire(f));
  printf ("Caractère lu : %c\n", lire_binaire(f));

  free_fichier (f);
/*  fichier ficR = ouvrir_fichier("test.bin", "rb");
  lire_binaire (ficR, 10);
  fermer_fichier(ficR);*/
}
