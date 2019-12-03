#include "fichier.h"

void calcul_frequences (fichier f) {
  int i ;

  // initialisation de frequences[] à 0
  for (i = 0 ; i < MAX_CHAR ; i++)  {
    frequences[i] = 0 ;
  }

  // BROUILLON
  while (f.read() != endOfFile) {
    int carCourant = (int)f.read() ;
    frequences[carCourant]++ ;
  }
}

void calcul_arbre_codage () {
  arbre tmp[MAX_CHAR] ;
  int i ;

  for (i = 0 ; i < MAX_CHAR ; i++) {
    tmp[i].poids = frequences[i];
    tmp[i].c = frequences[i];
  }
}
