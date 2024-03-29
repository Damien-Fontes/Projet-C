#ifndef __FICHIER_H__
#define __FICHIER_H__

#define BLOCK_SIZE 256

typedef struct{
  FILE * fic;
  char * nom;
  char * mode;
  unsigned char octet[8];
  unsigned char buffer[256];

  int iOctet;
  int iBuffer;
  int remplissage;
  long unsigned int nbOctet;
  long unsigned int nbOctetLu;

}Fichier;

Fichier * creer_fichier (char * nom, char * mode);
void free_fichier (Fichier *fic);
void ouvrir_fichier (Fichier *fic, char*nom, char * mode);
void ecrire_bit (Fichier *fic, unsigned char bit);
void fermer_fichier (Fichier * fic, char * mode);
unsigned char lire_binaire (Fichier *fic);
unsigned char lire_char (Fichier * fic);
void ecrire_char (Fichier * fic, char c);
#endif
