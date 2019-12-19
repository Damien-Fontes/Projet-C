#ifndef __ARBRE_H__
#define __ARBRE_H__

typedef struct {
	char c;
	int occurrence;
	char encodage[256];
} Elt;

struct znoeud {
  Elt elt;
  struct znoeud * fils_gauche;
  struct znoeud * fils_droit;
  struct znoeud * suiv;
};

typedef struct znoeud noeud;
typedef struct znoeud * arbre;

arbre creer_arbre (Elt x, arbre fg, arbre fd);
arbre creer_arbre_vide ();
int est_arbre_vide (arbre a);
Elt racine (arbre a);
arbre fils_gauche (arbre a);
arbre fils_droit (arbre a);
int est_feuille (arbre a);
arbre detruire_arbre (arbre a);
int nb_feuilles (arbre a);
void print_arbre_aux(arbre a);
void print_arbre(arbre a) ;
#endif
