#ifndef __FICHIER_H__
#define __FICHIER_H__

struct Fichier {
  FILE * fic;
  char * nom;
  char * buffer;
  char * octet;

  int iOctet;
  int iBuffer;

};
#endif
