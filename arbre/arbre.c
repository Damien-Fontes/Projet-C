#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "arbre.h"

arbre creer_arbre (Elt x, arbre fg, arbre fd) {
  noeud * nouveau;
  nouveau = (noeud*) malloc (sizeof(noeud));
  nouveau->elt = x;
  nouveau->fils_gauche = fg;
  nouveau->fils_droit = fd;
  //pour le parcour en largeur
  nouveau->suiv = NULL;
  return nouveau;
}

arbre creer_arbre_vide () {
  return NULL ;
}

int est_arbre_vide (arbre a) {
  return (a==NULL);
}

Elt racine (arbre a) {
  assert(!est_arbre_vide(a));
  return a->elt;
}

arbre fils_gauche (arbre a) {
  assert(!est_arbre_vide(a));
  return a->fils_gauche;
}

arbre fils_droit (arbre a) {
  assert(!est_arbre_vide(a));
  return a->fils_droit;
}

int est_feuille (arbre a) {
  if (est_arbre_vide(a))
    return 0;
  return (est_arbre_vide(fils_gauche(a)) && est_arbre_vide(fils_gauche(a)));
}


arbre detruire_arbre (arbre a) {
  if (!est_arbre_vide(a)) {
    detruire_arbre(fils_gauche(a));
    detruire_arbre(fils_droit(a));
    free (a);
  }
  return NULL;
}

int nb_feuilles (arbre a) {
  if (est_arbre_vide(a))
    return 0;
  if (est_feuille(a))
    return 1;
  return nb_feuilles (fils_gauche(a)) + nb_feuilles(fils_droit(a));
}

void print_arbre_aux(arbre a)
{
  if (est_arbre_vide(a)) {
    printf(".") ;
  } else {
    printf("%c, %d \n (", a->elt.c, a->elt.occurrence) ;
    print_arbre_aux(a->fils_gauche) ;
    printf(") (");
    print_arbre_aux(a->fils_droit) ;
    printf(")\n") ;
  }
}

void print_arbre(arbre a) // Notation préfixe
{
  print_arbre_aux(a) ;
  printf("\n") ;
}
