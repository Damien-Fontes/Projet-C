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
  long unsigned int nbOctet = fic->nbOctet;
  if (strcmp(mode,"wb")==0) {
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

unsigned char lire_fic (Fichier * fic) {
  fread (fic->buffer, 1, 1, fic->fic);
  return (unsigned char)fic->buffer[0];
}

unsigned char lire_binaire (Fichier *fic) {
  int i;
  unsigned char bit;
  unsigned char d, d_temp;
  d = 0x80;


  if (fic->nbOctetLu == 0) {
    fic->nbOctetLu = fread (fic->buffer, 1, sizeof(fic->buffer), fic->fic);
    printf("nbOctetLu : %ld\n", fic->nbOctetLu);
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
//
// void main () {
//   Fichier *f;
//   f = creer_fichier (f, "../test.bin", "wb");
//   //ouvrir_fichier(f,"../test.bin", "wb");
//
//   //Octet 0
//   ecrire_bit (f, '0');
//   ecrire_bit (f, '0');
//   ecrire_bit (f, '0');
//   ecrire_bit (f, '1');
//   ecrire_bit (f, '0');
//   ecrire_bit (f, '0');
//   ecrire_bit (f, '1');
//   ecrire_bit (f, '1');
//   //Octet 1
//   ecrire_bit (f, '0');
//   ecrire_bit (f, '0');
//   ecrire_bit (f, '0');
//   ecrire_bit (f, '1');
//   ecrire_bit (f, '1');
//   ecrire_bit (f, '1');
//   ecrire_bit (f, '1');
//   ecrire_bit (f, '1');
//   //Octet 3
//   /*ecrire_bit (f, '0');
//   ecrire_bit (f, '1');*/
//   fermer_fichier(f, "wb");
//
//   Fichier * f2;
//   f2 =(Fichier*) malloc (sizeof(Fichier));
//   ouvrir_fichier(f2, "../test.bin", "rb");
//   printf ("Caractère lu : %c\n", lire_binaire(f2));
//   printf ("Caractère lu : %c\n", lire_binaire(f2));
//   printf ("Caractère lu : %c\n", lire_binaire(f2));
//   printf ("Caractère lu : %c\n", lire_binaire(f2));
//   printf ("Caractère lu : %c\n", lire_binaire(f2));
//   printf ("Caractère lu : %c\n", lire_binaire(f2));
//   printf ("Caractère lu : %c\n", lire_binaire(f2));
//   printf ("Caractère lu : %c\n", lire_binaire(f2));
//
//   printf ("\nCaractère lu : %c\n", lire_binaire(f2));
//   printf ("Caractère lu : %c\n", lire_binaire(f2));
//   printf ("Caractère lu : %c\n", lire_binaire(f2));
//   printf ("Caractère lu : %c\n", lire_binaire(f2));
//   printf ("Caractère lu : %c\n", lire_binaire(f2));
//   printf ("Caractère lu : %c\n", lire_binaire(f2));
//   printf ("Caractère lu : %c\n", lire_binaire(f2));
//   printf ("Caractère lu : %c\n", lire_binaire(f2));
//   fermer_fichier(f2, "rb");
//
// /*  fichier ficR = ouvrir_fichier("test.bin", "rb");
//   lire_binaire (ficR, 10);
//   fermer_fichier(ficR);*/
// }
