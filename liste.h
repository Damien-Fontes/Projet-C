/*Exercice 1*/

#ifndef __LIST_H__
#define __LIST_H__

typedef int Elt;

struct zMaillon {
  Elt elt;
  struct zMaillon * suiv;
};

typedef struct zMaillon Maillon;
typedef Maillon * Liste;

Liste CreeListeVide();
Liste LibererListe(Liste l);
Liste LibererMaillon(Maillon *m);
Liste AjoutListe(Liste l, Elt x);
Liste QueueListe(Liste l);
Elt TeteList (Liste l);
int EstListeVide(Liste l);

#endif
