#ifndef __FICHIER_H__
#define __FICHIER_H__

typedef struct{
  FILE * fic;
  char * nom;
  char * buffer;
  char * octet;

  int iOctet;
  int iBuffer;

}Fichier;

Fichier init_fichier (Fichier fic, char * nom);
Fichier ouvrir_fichier (Fichier fic, char * mode);
void ecrire_bit (Fichier fic, char bit);
void ecrire_buffer (Fichier fic);
void ecrire_binaire (Fichier fic);
void lire_binaire (Fichier fic, char * buffer);
void fermer_fichier (Fichier fic);
//bool fichier_existe(char* filename);

#endif
