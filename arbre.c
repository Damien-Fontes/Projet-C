#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "liste.h"
#include "file.h"
#include "arbre.h"
#include "fileArbre.h"

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

void afficher_racine (arbre a) {
  if(!est_arbre_vide(a))
    printf("%d\n", racine(a));
}

void profondeur_prefixe (arbre a, void action (arbre)) {
  if (!est_arbre_vide(a)) {
    action(a);
    profondeur_prefixe(fils_gauche(a), action);
    profondeur_prefixe(fils_droit(a), action);
  }
  return;
}

void largeur (arbre a, void action(arbre)) {
  fileArbre fa;
  arbre aa;
  assert(!est_arbre_vide(a));
  creer_file_vide(&fa);
  fa_enfiler(&fa, a);
  while (!est_file_vide(fa)) {
    aa = fa_defiler (&fa);
    action(aa);
    if (fils_gauche(aa))
      fa_enfiler (&fa, fils_gauche(aa));
    afficherFileArbre(fa);
    if (fils_droit(aa))
      fa_enfiler (&fa, fils_droit(aa));
    afficherFileArbre(fa);
    //afficherFileArbre(fa);
  }
}

int hauteur (arbre a) {
  int hg, hd;

  if (est_arbre_vide(a))
    return 0;

  hg = hauteur(fils_gauche(a));
  hd = hauteur(fils_droit(a));

  if (hg >= hd)
    return ++hg;

  return ++hd;
}

int nb_feuilles (arbre a) {
  if (est_arbre_vide(a))
    return 0;
  if (est_feuille(a))
    return 1;
  return nb_feuilles (fils_gauche(a)) + nb_feuilles(fils_droit(a));
}

noeud * rechercher (arbre a, Elt e) {
  noeud * n;
  if (est_arbre_vide(a)) {
    return NULL;
  }
  if (racine(a)==e)
    return a;
  n = rechercher(fils_gauche(a), e);
  if (!n)
    n = rechercher(fils_droit(a), e);
  return n;
}

int egalite (arbre a, arbre b) {
  int ok;

  if (!est_arbre_vide(a) && est_arbre_vide(b)) return 0;
  if (est_arbre_vide(a) && !est_arbre_vide(b)) return 0;
  if (est_arbre_vide(a) && est_arbre_vide(b)) return 1;
  if (racine(a) != racine(b)) return 0;

  ok = egalite (fils_gauche(a), fils_gauche(b));
  if (ok) ok = egalite (fils_droit(a), fils_droit(b));

  return ok;
}

int est_sous_arbre (arbre a, arbre b) {
  int ok;
  ok = 0;

  if (!est_arbre_vide(a)) {
    ok = egalite (a,b);
    if (!ok) {
      ok = est_sous_arbre (fils_gauche(a),b);
      if (!ok) ok = est_sous_arbre (fils_droit(a),b);
    }
  }
  return ok;
}

int iterer (arbre a, int action(int, int), int acc) {
  if (est_arbre_vide(a)) return acc;
  acc=action(acc, racine (a));
  acc=iterer(fils_gauche(a), action, acc);
  acc=iterer(fils_droit(a), action, acc);
  return acc;
}

int soustraction (int a, int b) {
  return a-b;
}

int addition (int a, int b) {
  return a+b;
}
