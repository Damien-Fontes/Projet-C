#include <stdlib.h>
#include "../fichier/fichier.h"
#include "../arbre/arbre.h"
#include "codage.h"

void calcul_frequences (Fichier f) {
  int i , j ;
  char * buffer;

  // initialisation de frequences[] à 0
  for (i = 0 ; i < MAX_CHAR ; i++)  {
    frequences[i].c = (char)i ;
    frequences[i].occurence = 0 ;
  }


  while (feof(f.fic)== NULL) {
    buffer = lire_binaire (f, buffer) ;

    j = 0 ;
    while (j < MAX_CHAR) {
      if (buffer == frequences[j].c) {
        frequences[j].occurence++ ;
        j = MAX_CHAR ;
      } else {
        j++ ;
      }
    }
  }
}

/*void calcul_arbre_codage () {
  arbre tmp[MAX_CHAR] ;
  int i ;

  for (i = 0 ; i < MAX_CHAR ; i++) {
    tmp[i].poids = frequences[i];
    tmp[i].c = frequences[i];
  }
}*/

/*
*
* MAIN DE TEST
*
*/

int main (void) {
  Fichier fichier = ouvrir_fichier("test.bin", "r") ;

  calcul_frequences(fichier);
  for (int i = 0 ; i < MAX_CHAR ; i++) {
    if (frequences[i].occurence != 0) {
      printf ("%c : %d \n", frequences[i].c, frequences[i].occurence) ;
    }
  }

}
