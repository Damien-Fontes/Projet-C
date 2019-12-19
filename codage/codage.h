#ifndef __CODAGE_H__
#define __CODAGE_H__


#define MAX_CHAR 256

Elt frequences[MAX_CHAR] ;
arbre arbre_codage;

void calcul_frequences (char * buffer);
void calcul_arbre_codage ();
void tableau_encodage (arbre *a, int i, char* encodage) ;
int get_pos (char c);

#endif
