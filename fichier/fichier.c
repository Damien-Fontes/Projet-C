#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

void free_fichier (Fichier *fic) {
  free (fic);
}

void ouvrir_fichier (Fichier *fic, char * nom, char * mode) {
  fic->fic = NULL;
  fic->mode = mode;
  fic->nom = nom;

  fic->fic = fopen (fic->nom, mode);

  fic->iOctet = 0;
  fic->iBuffer = 0;
  fic->nbOctet = 0;
  fic->nbOctetLu = 0;
  printf("Fichier ouvert : %s, Mode : %s\n", fic->nom, mode);
}

void ecrire_bit (Fichier * fic, unsigned char bit) {
  int i;
  unsigned char b, octet;
  fic->octet[fic->iOctet++] = bit;

  if (fic->iOctet == 8) {
    octet = 0;
    b = 0x80;

    for (i = 0; i < 8; i++) {
      if (fic->octet[i] == '1')
        octet = octet | b;
      b = b >> 1;
    }

    fic->iOctet = 0;

    printf("iBuffer : %d\n", fic->iBuffer);
    fic->buffer[fic->iBuffer++] = octet;
    //fic->iBuffer++;
    fic->nbOctet++;

    if (fic->iBuffer == BLOCK_SIZE) {
      fwrite (&fic->buffer,1,fic->nbOctet,fic->fic);
      fic->iBuffer = 0;
    }

      printf("Ecriture dans le fichier.\n" );
      printf("Buffer : %s\n",fic->buffer);
    }
}

void fermer_fichier (Fichier * fic, char * mode) {
  int octet, b, i;
  int nbOctet = fic->nbOctet;
  if (mode = "wb") {
    printf ("mode = wb\n");
    if (fic->iOctet != 0) {
      octet = 0;
      b = 0x80;
      for (i = 0; i<fic->iOctet; i++) {
        if (fic->octet[i] == '1')
          octet = octet|b;
        b = b >> 1;
      }
      octet = fic->buffer[fic->iBuffer++];
      fic->iBuffer++;
      nbOctet++;
  }
  if (fic->iBuffer != 0)
    fwrite (&fic->buffer,1,nbOctet,fic->fic);
  }
  fclose(fic->fic);
  free_fichier(fic);
}

unsigned char lire_binaire (Fichier *fic) {
  int i;
  unsigned char bit;
  unsigned char d;
  d = 0x80;

  if (fic->nbOctetLu == 0) {
    fic->nbOctetLu = fread (fic->buffer, 1, sizeof(fic->buffer), fic->fic);
    printf("nbOctetLu : %d\n", fic->nbOctetLu);
    fic->iBuffer = 0;
    for (i = 0; i<8; i++) {
      if (fic->buffer[fic->iBuffer] == '1')
        fic->octet[i] = fic->buffer[fic->iBuffer]&d;
      d = d >> 1;
    }
    fic->iBuffer++;
    fic->iOctet = 0;
    fic->nbOctet = fic->nbOctet + fic->nbOctetLu;
  }

  bit = fic->octet[fic->iOctet];
  fic->iOctet++;

  if (fic->iOctet == 8) {
    printf("Octet full\n");
    for (i = 0; i<8; i++) {
      if (fic->buffer[fic->iBuffer] == '1')
        fic->octet[i] = fic->buffer[fic->iBuffer]&d;
      d = d >> 1;
    }
    fic->iBuffer++;
    fic->iOctet = 0;

    if (fic->iBuffer == BLOCK_SIZE)
      fic->nbOctetLu = 0;
  }
  return bit;
}

void main () {
  Fichier * f;
  f =(Fichier*) malloc (sizeof(Fichier));
  ouvrir_fichier(f,"../test.bin", "wb");

  //Octet 0
  ecrire_bit (f, '0');
  ecrire_bit (f, '0');
  ecrire_bit (f, '0');
  ecrire_bit (f, '1');
  ecrire_bit (f, '0');
  ecrire_bit (f, '0');
  ecrire_bit (f, '1');
  ecrire_bit (f, '1');
  //Octet 1
  ecrire_bit (f, 'd');
  ecrire_bit (f, '2');
  ecrire_bit (f, 'a');
  ecrire_bit (f, '2');
  ecrire_bit (f, 'b');
  ecrire_bit (f, 'c');
  ecrire_bit (f, 'b');
  ecrire_bit (f, 'c');
  //Octet 3
  ecrire_bit (f, '3');
  ecrire_bit (f, '4');
  fermer_fichier(f, "wb");

  Fichier * f2;
  f2 =(Fichier*) malloc (sizeof(Fichier));
  ouvrir_fichier(f2, "../test.bin", "rb");
  printf ("Caractère lu : %c\n", lire_binaire(f2));
  printf ("Caractère lu : %c\n", lire_binaire(f2));
  printf ("Caractère lu : %c\n", lire_binaire(f2));
  printf ("Caractère lu : %c\n", lire_binaire(f2));
  printf ("Caractère lu : %c\n", lire_binaire(f2));
  printf ("Caractère lu : %c\n", lire_binaire(f2));
  printf ("Caractère lu : %c\n", lire_binaire(f2));
  printf ("Caractère lu : %c\n", lire_binaire(f2));
  printf ("Caractère lu : %c\n", lire_binaire(f2));
  printf ("Caractère lu : %c\n", lire_binaire(f2));
  printf ("Caractère lu : %c\n", lire_binaire(f2));
  printf ("Caractère lu : %c\n", lire_binaire(f2));
  fermer_fichier(f2, "rb");

/*  fichier ficR = ouvrir_fichier("test.bin", "rb");
  lire_binaire (ficR, 10);
  fermer_fichier(ficR);*/
}
