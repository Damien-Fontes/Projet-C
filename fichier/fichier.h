#ifndef __FICHIER_H__
#define __FICHIER_H__

#define BLOCK_SIZE 4096

typedef struct{
  FILE * fic;
  char * nom;
  char * mode;
  unsigned char octet[8];
  unsigned char buffer[256];

  int iOctet;
  int iBuffer;
  int nbOctet;
  int nbOctetLu;

}Fichier;

Fichier * creer_fichier (Fichier *f, char * nom, char * mode);
void free_fichier (Fichier *fic);
void ouvrir_fichier (Fichier *fic, char * mode);
void ecrire_bit (Fichier *fic, unsigned char bit);
void fermer_fichier (Fichier * fic, char * mode);
unsigned char lire_binaire (Fichier *fic);
unsigned char lire_fic (Fichier * fic);
#endif
