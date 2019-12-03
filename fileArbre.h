#ifndef __FILEARBRE_H__
#define __FILEARBRE_H__

typedef struct FArbre {
  noeud * premier;
  noeud * dernier;
}fileArbre;

void creer_file_vide (fileArbre * fa);
int est_file_vide (fileArbre fa);
void fa_enfiler (fileArbre * fa, arbre a);
arbre fa_defiler (fileArbre * fa);
void afficherFileArbre (fileArbre fa) ;
#endif
