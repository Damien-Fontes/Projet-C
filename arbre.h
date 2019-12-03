#ifndef __ARBRE_H__
#define __ARBRE_H__


typedef int Elt;

struct znoeud {
  Elt elt;
  struct znoeud * fils_gauche;
  struct znoeud * fils_droit;
  struct znoeud * suiv;
};

typedef struct znoeud noeud;
typedef struct znoeud * arbre;

arbre creer_arbre (Elt x, arbre fg, arbre fd);
int est_arbre_vide (arbre a);
Elt racine (arbre a);
arbre fils_gauche (arbre a);
arbre fils_droit (arbre a);
int est_feuille (arbre a);
arbre detruire_arbre (arbre a);
void profondeur_prefixe (arbre a, void action (arbre));
void largeur (arbre a, void action(arbre));
void afficher_racine (arbre a);
int hauteur (arbre a);
int nb_feuilles (arbre a);
int egalite (arbre a, arbre b);
noeud * rechercher (arbre a, Elt e);
int est_sous_arbre (arbre a, arbre b);
int iterer (arbre a, int action(int, int), int acc);
int soustraction (int a, int b);
int addition (int a, int b);
#endif
