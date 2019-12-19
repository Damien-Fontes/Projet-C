#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

  // construction de l'arbre
  while ((codage[0] != NULL) && (codage[1] != NULL)) {
    elt_tmp.c = '$';
    elt_tmp.occurrence = racine(codage[0]).occurrence + racine(codage[1]).occurrence;

    arbre_tmp = creer_arbre (elt_tmp, codage[0], codage[1]);

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
  while (c != frequences[i].c && i != MAX_CHAR-1) {
    i++;
  }
  if (c == frequences[i].c)
    return i;
  else
    return -1;
}

void tableau_encodage (arbre a, int i, char* encodage) {
  if (fils_gauche(a) == NULL && fils_droit(a) == NULL) {
    encodage[i] = '\0';
    int j = 0;
    for (j; j <= i; j++)
      frequences[get_pos(racine(a).c)].encodage[j] = encodage[j];
  }
  else {
    encodage[i] = '1';
    tableau_encodage (fils_gauche(a), i+1, encodage);
    encodage[i] = '0';
    tableau_encodage (fils_droit(a), i+1, encodage);
  }
}

void tableau_ecrire (arbre a, char * tableau, int *iTableau) {
  if (fils_gauche(a) == NULL && fils_droit(a) == NULL) {
    tableau[*iTableau] = '(';
    *iTableau = *iTableau + 1;
    tableau[*iTableau] = racine(a).c;
    *iTableau = *iTableau + 1;
    tableau[*iTableau] = ')';
    *iTableau = *iTableau + 1;
    return;
  }
  else {
    if (fils_gauche(a) != NULL) {
      tableau[*iTableau] =  '1';
      *iTableau = *iTableau + 1;
      tableau_ecrire (fils_gauche(a), tableau, iTableau);
    }

    if (fils_droit(a) != NULL) {
      tableau[*iTableau] =  '0';
      *iTableau = *iTableau + 1;
      tableau_ecrire (fils_droit(a), tableau, iTableau);
    }
  }
}

arbre decoder_arbre (char * tableau_Arbre, int * i) {
  Elt elt_tmp;
  elt_tmp.c = '$';
  elt_tmp.occurrence = 0;

  if (tableau_Arbre[*i] == '(') {
    *i = *i+1;
    arbre a = creer_arbre (elt_tmp, NULL, NULL);
    a->elt.c = tableau_Arbre[*i];
    *i = *i+2;
    return a;
  }
  else {
    arbre fg = NULL;
    arbre fd = NULL;
    if (tableau_Arbre[*i] == '1') {
      *i = *i+1;
      fg = decoder_arbre (tableau_Arbre, i);
    }
    if (tableau_Arbre[*i] == '0') {
      *i = *i+1;
      fd = decoder_arbre (tableau_Arbre, i);
    }
    arbre a = creer_arbre (elt_tmp, fg, fd);
    return a;
  }
  return NULL;
}

void decoder_message_rec (char * TEncoder, char * TRes, int * iEncoder, int * iRes, int tailleT) {
  while (*iEncoder != tailleT) {
    decoder_message (arbre_codage, TEncoder, TRes, iEncoder, iRes);
  }
}

void decoder_message (arbre a, char * TEncoder, char * TRes, int * iEncoder, int * iRes) {
  // printf("IEncder : %d, IRes : %d\n", *iEncoder, *iRes);
  if (fils_gauche(a) == NULL && fils_droit(a) == NULL) {
    TRes[*iRes] = racine(a).c;
    *iRes = *iRes+1;
    return;
  }

  else if (TEncoder[*iEncoder] == '1') {
    *iEncoder = *iEncoder+1;
    decoder_message (fils_gauche(a), TEncoder, TRes, iEncoder, iRes);
  }

  else if (TEncoder[*iEncoder] == '0') {
    *iEncoder = *iEncoder+1;
    decoder_message (fils_droit(a), TEncoder, TRes, iEncoder, iRes);
  }
  return;
}
