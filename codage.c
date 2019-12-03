#include "fichier.h"

void calcul_frequences (fichier f) {
  int somme, i ;

  for (i = 0 ; i < MAX_CHAR ; i++) {
    frequences[i] = 0 ;
  }

  // BROUILLON
  while (f.read() != endOfFile) {
    int carCourant = (int)f.read() ;
    frequences[carCourant]++ ;
  }
}

void calcul_arbre_codage () {
  
}
