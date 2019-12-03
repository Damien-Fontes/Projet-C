#include <stdio.h>
#include <assert.h>
#include "liste.h"
#include "arbre.h"

int main(int argc, char const *argv[]) {
  int acc;
  acc=0;

  arbre a, a1, a2, a3, a4, a5;
  a3 = creer_arbre(5, NULL, NULL);
  a4 = creer_arbre(1, NULL, NULL);
  a5 = creer_arbre(6, NULL, NULL);
  a1 = creer_arbre(3, a3, NULL);
  a2 = creer_arbre(2, a4, a5);
  a = creer_arbre(5, a1, a2);

  arbre b, b1, b2, b3, b4, b5;
  b3 = creer_arbre(5, NULL, NULL);
  b4 = creer_arbre(1, NULL, NULL);
  b5 = creer_arbre(6, NULL, NULL);
  b1 = creer_arbre(3, b3, NULL);
  b2 = creer_arbre(2, b4, b5);
  b = creer_arbre(5, b1, b2);

  detruire_arbre (a);
  detruire_arbre (b);
  return 0;
}
