#ifndef __CODAGE_H__
#define __CODAGE_H__


#define MAX_CHAR 256

Elt frequences[MAX_CHAR] ;
arbre arbre_codage;

void calcul_frequences (char * buffer);
void calcul_arbre_codage ();
void tableau_encodage (arbre a, int i, char* encodage) ;
int get_pos (char c);
void tableau_ecrire (arbre a, char * tableau, int *iTableau);
arbre decoder_arbre (char * tableau_Arbre, int * i);
void decoder_message_rec (char * TEncoder, char * TRes, int * iEncoder, int * iRes, int tailleT);
void decoder_message (arbre a, char * TEncoder, char * TRes, int * iEncoder, int * iRes);
#endif
