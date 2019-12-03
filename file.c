#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "liste.h"
#include "file.h"
#include "arbre.h"

void creeFileVide (File * file) {
  file->premier = NULL;
  file->dernier = NULL;
}

int estFileVide (File file) {
  return (file.premier==NULL);
}

void enfiler (File * file, Elt x) {
  Maillon * nouveau;
  nouveau = (Maillon *)malloc(sizeof(Maillon));
  nouveau->elt = x;
  nouveau->suiv = NULL;

  if (estFileVide(*file)) {
    file->premier = nouveau;
    file->dernier = file->premier;
  }
  else
    file->dernier->suiv = nouveau;
    file->dernier = nouveau;
}

Elt defiler (File * file) {
  Elt x;
  Maillon * m;

  //assert(estFileVide(*file));
  x = TeteList(file->premier);
  m = QueueListe(file->premier);

  if(file->premier == file->dernier)
    file->dernier == NULL;
  free(file->premier);
  file->premier = m;

  return x;
}

void afficherFile (File file) {
  printf("\n---\n");
  while(!estFileVide(file)) {
      printf("%d ", TeteList(file.premier));
      file.premier = file.premier->suiv;
  }
  printf("\n---\n");
}
