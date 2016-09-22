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
  algue *a = (algue *)malloc(sizeof(algue));
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

void detruire_algue(void **pt) {
  if (*pt != NULL) {
    free(*pt);
    (*pt) = NULL;
  }
}

/* à définir */
liste algue_liste_init(void (*_copier)(void *val, void **pt),
                       void (*_afficher)(FILE *f, void *val),
                       void (*_detruire)(void **pt)) {
  liste l = liste_creer(_copier, _afficher, _detruire);
  algue *p_a = algue_valeur(T1, GAUCHE);
  liste_insertion_debut(l, p_a);
  free(p_a);
  return l;
}

/*!
* A appeler après une itération. Vérifie que toute les algues de la liste ont
* une taille inférieur à TMAX
*/
void test_algue_iteration(liste l) {
  assert(l != NULL);

  liste_courant_init(l);
  unsigned int taille = liste_taille(l);
  for (size_t i = 0; i < taille; i++) {
    assert(((algue *)liste_valeur_courant(l))->taille <= TMAX);
  }
}

/* une itération consiste à visiter tous les éléments de la liste */
/* et à faire évoluer chaque cellule selon la règle (cf énoncé) */
void algue_iteration(liste l) {
  assert(l != NULL);
  liste_courant_init(l);
  int i = 0;
  int tailleOriginale = liste_taille(l);
  while (i < tailleOriginale) {
    // Si l'algue a une taille supérieure à TMAX, je la divise.
    if (((algue *)liste_valeur_courant(l))->taille >= TMAX) {
      // La petite algue est toujours dans la même orientation que l'algue
      // courante. (- orientation) revient à dire l'orientation opposée (ex:
      // gauche est l'opposé de droite)
      algue *p_petiteAlgue =
          algue_valeur(T1, ((algue *)liste_valeur_courant(l))->orientation);
      algue *p_moyenneAlgue =
          algue_valeur(T2, -(((algue *)liste_valeur_courant(l))->orientation));
      if (p_petiteAlgue->orientation == GAUCHE) {
        liste_insertion_avant(l, p_petiteAlgue);
        liste_insertion_apres(l, p_moyenneAlgue);
      } else {
        liste_insertion_apres(l, p_petiteAlgue);
        liste_insertion_avant(l, p_moyenneAlgue);
      }
      free(p_petiteAlgue);
      free(p_moyenneAlgue);
      liste_courant_suivant(l);   // Je passe sur la nouvelle algue de droite
      liste_suppression_avant(l); // Je supprime l'ancienne algue courante
    } else {                      // Sinon j'augmente sa taille
      ((algue *)liste_valeur_courant(l))->taille++;
    }
    // Je passe sur la prochaine prochaine algue à vérifier
    liste_courant_suivant(l);
    i++;
  }
  test_algue_iteration(l);
}

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
