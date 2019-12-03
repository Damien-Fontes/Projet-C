#ifndef __FILE_H__
#define __FILE_H__

typedef struct File {
  Maillon * premier;
  Maillon * dernier;
}File;

void creeFileVide(File * file);
int estFileVide(File file);
void enfiler (File * file, Elt x);
Elt defiler (File * file);
void afficherFile (File file);
#endif
