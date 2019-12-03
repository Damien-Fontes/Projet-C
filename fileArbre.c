#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "arbre.h"
#include "fileArbre.h"

void creer_file_vide (fileArbre * fa) {
  fa->premier = NULL;
  fa->dernier = NULL;
}

int est_file_vide (fileArbre fa) {
  return (fa.premier==NULL);
}

void fa_enfiler (fileArbre * fa, arbre a) {
  noeud * n;
  n = (noeud *)malloc(sizeof(noeud));
  n->elt = a->elt;
  printf("elt <-- %d\n", n->elt);
  n->fils_gauche = fils_gauche(a);
  n->fils_droit = fils_droit(a);
  n->suiv = NULL;
  if (est_file_vide(*fa)) {
    fa->premier = n;
    fa->dernier = fa->premier;
    afficherFileArbre(*fa);
  }
  else {
    fa->dernier->suiv = n;
    fa->dernier = n;
  }

  //printf("elt premier <-- %d\n", fa->premier->elt);
  //printf("elt dernier <-- %d\n", fa->dernier->elt);
}

arbre fa_defiler (fileArbre * fa) {
  arbre a;
  noeud * n;

  //assert(estFileVide(*file));
  a = fa->premier;
  n = fa->premier->suiv;

  if(fa->premier == fa->dernier)
    fa->dernier == NULL;
  free(fa->premier);
  fa->premier = n;

  printf("elt --> %d\n", a->elt);
  return a;
}

void afficherFileArbre (fileArbre fa) {
  printf("\n---\n");
  while(!est_file_vide(fa)) {
      printf("%d ", racine(fa.premier));
      fa.premier = fa.premier->suiv;
  }
  printf("\n---\n");
}
