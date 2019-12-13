#include <stdio.h>
#include <stdlib.h>
#include "../fichier/fichier.h"
#include "../arbre/arbre.h"
#include "codage.h"

// void calcul_frequences (Fichier * f) {
//   int i , j ;
//   char * buffer;
//
//   // initialisation de frequences[] à 0
//   for (i = 0 ; i < MAX_CHAR ; i++)  {
//     frequences[i].c = (char)i ;
//     frequences[i].occurrence = 0 ;
//   }
//
//
//   while (feof(f->fic) == 0) {
//     buffer = lire_binaire (f, buffer) ;
//
//     j = 0 ;
//     while (j < MAX_CHAR) {
//       if (buffer == frequences[j].c) {
//         frequences[j].occurrence++ ;
//         j = MAX_CHAR ;  // sortie de la boucle
//       } else {
//         j++ ;
//       }
//     }
//   }
// }

void calcul_arbre_codage() {
  arbre codage[MAX_CHAR] ;
  arbre arbre_tmp ;
  Elt elt_tmp ;
  int i, j, k ;

  // remplissage de codage[] selon les frequences
  for (i = 0 ; i < MAX_CHAR ; i++) {
    if (frequences[i].occurrence != 0) {
      elt_tmp.c = (char)frequences[i].c ;
      elt_tmp.occurrence = frequences[i].occurrence ;
      codage[i] = creer_arbre (elt_tmp, creer_arbre_vide(), creer_arbre_vide());
    }
  }

  // ICI TRIER codage SELON occurrence

  // construction de l'arbre
  while ((codage[0] != NULL) && (codage[1] != NULL)) {
    elt_tmp.c = '\0';
    elt_tmp.occurrence = racine(codage[0]).occurrence + racine(codage[0]).occurrence;

    arbre_tmp = creer_arbre (elt_tmp, codage[0], codage[1]);

    detruire_arbre(codage[0]);
    detruire_arbre(codage[1]);

    // decaler codage
    for (i = 0 ; i < MAX_CHAR - 2 ; i++) {
      codage[i] = codage[i + 2] ;
    }

    // inserer arbre_tmp
    i = 0 ;
    while (racine(codage[i]).occurrence < racine(arbre_tmp).occurrence) {
      i++;
    }

    j = 0 ;
    while (codage[j] != NULL) {
      j++;
    }

    for (k = j ; k > i ; k--) {
      codage[k] = codage[k - 1];
    }

    codage[i] = arbre_tmp;
  }

  arbre_codage = codage[0] ;
}


/*
*
* MAIN DE TEST
*
*/
int main (void) {
  /*
  //TEST DE calcul_frequences
  Fichier * fichier ;
  char * nom = "test.bin" ;
  init_fichier(fichier, nom) ;
  ouvrir_fichier(fichier, "r") ;

  calcul_frequences(fichier);
  for (int i = 0 ; i < MAX_CHAR ; i++) {
    if (frequences[i].occurrence != 0) {
      printf ("%c : %d \n", frequences[i].c, frequences[i].occurrence) ;
    }
  }*/

  // initialisation de frequences
  for (int i = 0 ; i < MAX_CHAR ; i ++) {
    if (i < 229) {
      frequences[i].c = (char)0 ;
      frequences[i].occurrence = 0 ;
    } else {
      frequences[i].c = (char)(i - 132) ;
      frequences[i].occurrence = (i - 132) ;
    }
  }

  calcul_arbre_codage();
  print_arbre(arbre_codage);
  return 0;
}
