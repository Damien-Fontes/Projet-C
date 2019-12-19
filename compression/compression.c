#include <stdio.h>
#include <string.h>
#include "../arbre/arbre.h"
#include "../codage/codage.h"
#include "../fichier/fichier.h"
#include "compression.h"

int compression (char * name) {
  int tailleFichier, i, j;
  Fichier * fic;
  fic = creer_fichier(name, "r");

  //Parcour pour Taille Fichier
  tailleFichier = 0;
  while(feof(fic->fic) == 0) {
    lire_char(fic);
    tailleFichier++;
  }
  fermer_fichier(fic, "r");
  // tailleFichier--;

  //Fichier dans text[]
  char text[tailleFichier];
  text[tailleFichier] = '\0';
  fic = creer_fichier(name, "r");
  for (i = 0; i<tailleFichier; i++) {
    text[i] = lire_char(fic);
  }
  fermer_fichier(fic, "r");

  calcul_frequences (text);
  calcul_arbre_codage();

  char encodage[256];
  tableau_encodage(arbre_codage, 0, encodage);

  //Encode l'arbre dans le fichier
  char tableau_encoder[256];
  int pt = 0;
  tableau_ecrire (arbre_codage, tableau_encoder, &pt);
  fic = creer_fichier("compresse.bin", "wb");
  for (i = 0; i< pt; i++) {
    ecrire_char (fic, tableau_encoder[i]);
  }
  ecrire_char (fic, '^');
  ecrire_char (fic, '^');

  //Encode le texte dans le fichier bin
  int pos = 0;
  for (i=0; i< tailleFichier; i++) {
    j = 0;
    pos = get_pos(text[i]);
    while (frequences[pos].encodage[j] != '\0') {
      ecrire_bit(fic, frequences[pos].encodage[j]);
      j++;
    }
  }

  fermer_fichier(fic, "wb");
  return 0;
}

int decompression (char * name) {
  int i = 0;
  int j = 0;
  int k = 0;
  //Obtenir taille de l'arbre
  Fichier * fic = creer_fichier (name, "r");
  while (1 == 1) {
    if (lire_char(fic) == '^') {
      i++;
      if (lire_char(fic) == '^') {
        i++;
        break;
      }
    }
    i++;
  }
  fermer_fichier (fic, "r");

  //Recupérer l'arbre
  char tableau_Arbre[i-2];
  fic = creer_fichier (name, "r");
  for (j = 0; j < i-2; j++) {
    tableau_Arbre[j] = lire_char(fic);
  }
  fermer_fichier (fic, "r");
  //Créer l'arbre
  int pt = 0;
  arbre_codage = decoder_arbre (tableau_Arbre,&pt);

  //Taille du message
  fic = creer_fichier (name, "r");
  while (feof(fic->fic) == 0) {
    lire_binaire(fic);
  }
  fermer_fichier (fic, "r");

  int octetEncode = fic->nbOctet;
  char tableau_encoder [(octetEncode-i)*8];
  fic = creer_fichier (name, "rb");

  //Récupérer le message sans l'arbre
  for (j = 0; j < i; j++) {
    lire_char(fic);
  }
  for (j=0; j < (octetEncode-i)*8; j++) {
      tableau_encoder[k++] = lire_binaire(fic);
  }
  int iEncoder = 0;
  int iRes = 0;
  char TRes[(octetEncode-i)*8];

  decoder_message_rec (tableau_encoder, TRes, &iEncoder, &iRes, (octetEncode-i)*8);
  fermer_fichier (fic, "r");
  name = "res.txt";
  fic = creer_fichier(name, "wb");
  for (i = 0; i<iRes; i++){
    ecrire_char(fic, TRes[i]);
  }
  fermer_fichier (fic, "wb");
}
