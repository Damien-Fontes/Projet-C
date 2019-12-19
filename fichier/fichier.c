#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"

void free_fichier (Fichier *fic) {
  free (fic);
}

Fichier * creer_fichier (char * nom, char * mode) {
  Fichier* f =(Fichier*) malloc (sizeof(Fichier));
  ouvrir_fichier (f, nom, mode);
  return f;
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
  fic->remplissage = 0;
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
    fic->buffer[fic->iBuffer++] = octet;
    fic->nbOctet++;

    if (fic->iBuffer == BLOCK_SIZE-1) {
      fwrite (&fic->buffer,1,255,fic->fic);
      fic->iBuffer = 0;
      fic->nbOctet = 0;
    }
  }
}

void ecrire_char (Fichier * fic, char c) {
  fic->buffer[fic->iBuffer++] = c;
  fic->nbOctet++;
  if (fic->iBuffer == BLOCK_SIZE) {
    fwrite (&fic->buffer,1,1,fic->fic);
    fic->iBuffer = 0;
  }
}

void fermer_fichier (Fichier * fic, char * mode) {
  int i;
  unsigned char octet, b;
  if (strcmp(mode,"wb")==0) {
    if (fic->iOctet != 0) {
      for (i = fic->iOctet; i < 8; i++) {
        fic->octet[i] = '0';
        fic->remplissage++;
      }

      octet = 0;
      b = 0x80;
      for (i = 0; i< 8; i++) {
        if (fic->octet[i] == '1')
          octet = octet|b;
        b = b >> 1;
      }
      fic->buffer[fic->iBuffer++] = octet;
      fic->nbOctet++;
    }
    if (fic->iBuffer != 0)
    fwrite (&fic->buffer,1,fic->nbOctet,fic->fic);
  }
  fclose(fic->fic);
  free_fichier(fic);
}

unsigned char lire_binaire (Fichier *fic) {
  int i;
  unsigned char bit;
  unsigned char d, d_temp;
  d = 0x80;


  if (fic->nbOctetLu == 0) {
    fic->nbOctetLu = fread (fic->buffer, 1, sizeof(fic->buffer), fic->fic);
    fic->iBuffer = 0;
    for (i = 0; i<8; i++) {
      d_temp = fic->buffer[fic->iBuffer]&d;
      if (d_temp != 0) {
        fic->octet[fic->iOctet] = '1';
      } else {
        fic->octet[fic->iOctet] = '0';
      }
      d = d>>1;
      fic->iOctet++;
    }
    fic->iBuffer++;
    fic->iOctet = 0;
    fic->nbOctet = fic->nbOctet + fic->nbOctetLu;
  }

  bit = fic->octet[fic->iOctet];
  // printf("i : %d, octet[i] : %c   ", fic->iOctet, fic->octet[fic->iOctet]);
  fic->iOctet++;

  if (fic->iOctet == 8) {

    fic->iOctet = 0;
    d = 0x80;
    for (i = 0; i<8; i++) {
      d_temp = fic->buffer[fic->iBuffer]&d;
      if (d_temp != 0) {
        fic->octet[fic->iOctet] = '1';
      } else {
        fic->octet[fic->iOctet] = '0';
      }
      d = d>>1;
      fic->iOctet++;
    }
    fic->iBuffer++;
    fic->iOctet = 0;

    if (fic->iBuffer == BLOCK_SIZE)
      fic->nbOctetLu = 0;
  }
  return bit;
}


unsigned char lire_char (Fichier * fic) {
  fread (fic->buffer, 1, 1, fic->fic);
  return fic->buffer[0];
}
