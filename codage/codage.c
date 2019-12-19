#include <stdio.h>
#include <stdlib.h>
#include "../fichier/fichier.h"
#include "../arbre/arbre.h"
#include "codage.h"

void calcul_frequences (char * buffer) {
  int i , j ;

  // initialisation de frequences[] à 0
  for (i = 0 ; i < MAX_CHAR ; i++)  {
    frequences[i].c = (char)i ;
    frequences[i].occurrence = 0 ;
  }

  j=0;
  while (buffer[j] != '\0') {
    for (i = 0; i< MAX_CHAR; i++)
    {
      if (buffer[j] == frequences[i].c) {
        frequences[i].occurrence++;
        i = MAX_CHAR;
      }
    }
    j++;
  }
}

void calcul_arbre_codage() {
  arbre codage[MAX_CHAR] ;
  arbre arbre_tmp ;
  Elt elt_tmp ;
  int i, j, k, cptCodage ;
  int tailleTableau;

  cptCodage = 0;
  tailleTableau = 0;

  // remplissage de codage[] selon les frequences
  for (i = 0 ; i < MAX_CHAR ; i++) {
    if (frequences[i].occurrence != 0) {
      elt_tmp.c = (char)frequences[i].c ;
      elt_tmp.occurrence = frequences[i].occurrence ;
      codage[cptCodage] = creer_arbre (elt_tmp, creer_arbre_vide(), creer_arbre_vide());
      tailleTableau++;
      cptCodage++;
    }
  }



  for (i = tailleTableau; i < MAX_CHAR; i++)
    codage[i] = NULL;

  // ICI TRIER codage SELON occurrence
  printf("taille tableau : %d\n",tailleTableau );
  for (i = 0; i < tailleTableau; i++) {
    for (j = 0; j < tailleTableau-1; j++) {
      //printf("i : %d, j : %d\n", i,j);
      if (codage[j]->elt.occurrence > codage[j+1]->elt.occurrence) {
          // printf("ok\n" );
           arbre_tmp = codage[j+1];
           codage[j+1] = codage[j];
           codage[j] = arbre_tmp;
      }
    }
  }

  // for (i = 0; i < tailleTableau; i++) {
  //   printf("%d\n",codage[i]->elt.occurrence);
  // }

  // construction de l'arbre
  while ((codage[0] != NULL) && (codage[1] != NULL)) {
    elt_tmp.c = '$';
    elt_tmp.occurrence = racine(codage[0]).occurrence + racine(codage[1]).occurrence;

    arbre_tmp = creer_arbre (elt_tmp, codage[0], codage[1]);

    //detruire_arbre(codage[0]);
    //detruire_arbre(codage[1]);

    // decaler codage
    for (i = 0 ; i < tailleTableau - 2 ; i++) {
      codage[i] = codage[i + 2] ;
    }

    codage[tailleTableau-1] = NULL;
    codage[tailleTableau] = NULL;
    tailleTableau = tailleTableau-2;

    // inserer arbre_tmp
    i = 0 ;
    while ((racine(codage[i]).occurrence < racine(arbre_tmp).occurrence) && i<tailleTableau) {
      i++;
    }

    for (k = tailleTableau; k > i ; k--) {
      codage[k] = codage[k - 1];
    }
    tailleTableau++;
    codage[i] = arbre_tmp;
  }
  arbre_codage = codage[0] ;
}

int get_pos (char c) {
  int i = 0;
  while (c != frequences[i].c && c != MAX_CHAR) {
    i++;
  }
  if (c == frequences[i].c)
    return i;
  else
    return -1;
}
void tableau_encodage (arbre *a, int i, char* encodage) {
  if (est_arbre_vide(a)) {
    encodage[i] = '\0';
    return;
  }
  if (est_feuille(a) != 0) {
    encodage[i] = '\0';
    strcpy(frequences[get_pos(racine(a).c)].encodage, encodage);
  }
  else {
    encodage[i] = '1';
    tableau_encodage (fils_gauche(a), i+1, encodage);
    encodage[i] = '0';
    tableau_encodage (fils_droit(a), i+1, encodage);
  }

}

// /*
// *
// * MAIN DE TEST
// *
// */
// int main (void) {
//   //TEST DE calcul_frequences
//   /*Fichier * fichier ;
//   char * nom = "test.bin" ;
//   init_fichier(fichier, nom) ;
//   ouvrir_fichier(fichier, "wb") ;*/
//
//   calcul_frequences();
//   for (int i = 0 ; i < MAX_CHAR ; i++) {
//     if (frequences[i].occurrence != 0) {
//       printf ("%c : %d \n", frequences[i].c, frequences[i].occurrence) ;
//     }
//   }
//
//
//   calcul_arbre_codage();
//   print_arbre(arbre_codage);
//   return 0;
// }
