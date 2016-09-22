#include "listes_generiques.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GAUCHE -1
#define DROITE 1
#define T1 4
#define T2 5
#define TMAX 9
#define NBITER 20

typedef struct algue {
  int taille;
  int orientation;
} algue;

algue *algue_init() {
  algue *a;
  a = (algue *)malloc(sizeof(algue));
  a->taille = T1;
  a->orientation = GAUCHE;
  return a;
}

algue *algue_valeur(int _taille, int _orientation) {
  algue *a;
  a = (algue *)malloc(sizeof(algue));
  a->taille = _taille;
  a->orientation = _orientation;
  return a;
}

void copier_algue(void *val, void **pt) {
  *pt = (algue *)malloc(sizeof(algue));
  memcpy(*pt, val, sizeof(algue));
}

void afficher_algue(FILE *f, void *val) {
  fprintf(f, "(%d,%d)", ((algue *)val)->taille, ((algue *)val)->orientation);
}

void detruire_algue(void **pt) { free(*pt); }

/* à définir */
liste algue_liste_init(void (*_copier)(void *val, void **pt),
                       void (*_afficher)(FILE *f, void *val),
                       void (*_detruire)(void **pt)) {}

/* une itération consiste à visiter tous les éléments de la liste */
/* et à faire évoluer chaque cellule selon la règle (cf énoncé) */
void algue_iteration(liste l) {}

int main(void) {
  liste l = algue_liste_init(&copier_algue, &afficher_algue, &detruire_algue);
  FILE *f_out = fopen("algues_out.txt", "w");

  fprintf(f_out, "la liste initiale\n");
  liste_affichage(f_out, l);
  fprintf(f_out, "\n");
  for (int i = 0; i < NBITER; i++)
    algue_iteration(l);
  fprintf(f_out, "la liste résultat de %d itérations\n", NBITER);
  liste_affichage(f_out, l);
  liste_detruire(&l);
  fclose(f_out);
  return 0;
}
