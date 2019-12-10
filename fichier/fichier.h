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
#endif
