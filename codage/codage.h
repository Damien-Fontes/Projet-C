#ifndef __CODAGE_H__
#define __CODAGE_H__


#define MAX_CHAR 256

typedef struct {
	char c;
  int occurence;
} occurence;
occurence frequences[MAX_CHAR] ;
arbre arbre_codage;

void calcul_frequences (Fichier f);
void calcul_arbre_codage ();

#endif
