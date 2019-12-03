#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "liste.h"

Liste CreeListeVide() {
  return NULL;
}

int EstListeVide(Liste l) {
  return (l==CreeListeVide());
}

Liste AjoutListe(Liste l, Elt x) {
  Liste nouveau;
  nouveau = (Liste) malloc (sizeof(Maillon));
  nouveau->elt = x;
  nouveau->suiv = l;
  return nouveau;
}

Elt TeteList(Liste l) {
  assert(!EstListeVide(l));
  return l->elt;
}

Liste QueueListe(Liste l) {
  assert(!EstListeVide(l));
  return l->suiv;
}

Liste LibererListe (Liste l) {
  if (!EstListeVide(l)) {
    LibererListe(QueueListe(l));
    free(l);
  }
  return NULL;
}

Liste LibererMaillon(Maillon *m) {
  Liste l;
  l = QueueListe(m);
  free(m);
  return l;
}
