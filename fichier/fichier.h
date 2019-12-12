#ifndef __FICHIER_H__
#define __FICHIER_H__

#define BLOCK_SIZE 4096

typedef struct{
  FILE * fic;
  char * nom;
  char octet[8];
  char buffer[256];

  int iOctet;
  int iBuffer;
  int nbOctet;
  int nbOctetLu;

}Fichier;

void init_fichier (Fichier * fic, char * nom);
void free_fichier (Fichier *fic);
void ouvrir_fichier (Fichier *fic, char * mode);
void ecrire_bit (Fichier *fic, char bit);
void ecrire_buffer (Fichier *fic);
void ecrire_binaire (Fichier *fic);
void fermer_fichier (Fichier * fic);
void verification_buffer (Fichier * fic);
char lire_binaire (Fichier *fic);
#endif
