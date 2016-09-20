#include "listes_int.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT_LISTE() assert(l != NULL);

#define ASSERT_LISTE_COURANT()                                                 \
  assert(l != NULL);                                                           \
  assert(l->courant != NULL);

/*! \file
 * \brief La documentation pour les parties (types, variables, fonctions…)
 * internes du modules sont documentées ici.
 *
 * \copyright PASD
 * \version 2016
 */

/*!
 * Structure servant à définir un élément de type int de la liste.
 * Cette structure n'est visible que depuis listes_int.c .
 * Les fonctions attenantes sont static pour être également masquées. */
struct maillon_struct {
  struct maillon_struct *precedent;
  int val;
  struct maillon_struct *suivant;
};

/*! Un maillon est un pointeur sur (référence vers) une struct maillon_struct .
 */
typedef struct maillon_struct *maillon;

/*!
 * Création d'un maillon dont la valeur est _val .
 * suivant et precedent doivent pointer sur ce maillon.
 * \param _val valeur à stocker dans le maillon.
 * \return nouveau maillon stockant _val et bouclant sur lui-même.
 */
static maillon maillon_creer(int const _val) {
  maillon m = malloc(sizeof(struct maillon_struct));
  m->precedent = m;
  m->val = _val;
  m->suivant = m;
  return m;
}

/*!
 * Test pour savoir si le maillon est unique ( bouclant sur lui-même et
 * correspondant à une liste de taille 1 ).
 * \param m maillon à tester.
 */
static bool maillon_est_unique(maillon const m) {
  return m == m->precedent && m == m->suivant;
}

/*!
 * Destruction de toute la liste chaînée.
 * \param m (pointeur sur un) maillon de la liste chaînée à détruire.
*/
static void maillon_detruire(maillon *const m) {
  maillon start = *m;
  maillon courant = (*m)->suivant;
  maillon suivant;
  while (courant != start) {
    suivant = courant->suivant;
    free(courant);
    courant = suivant;
  }
  free(courant);
  *m = NULL;
}

/*!
 * Affichage d'un ensemble de maillon à partir d'un début et d'une fin.
 * Le résultat est de la forme \verbatim[ 1 2 3 ]\endverbatim sans saut de
 * ligne.
 * \param f flux où imprimer.
 * \param m_debut premier maillon à imprimer.
 * \param m_fin dernier maillon à imprimer.
 */
static void maillon_afficher(FILE *const f, maillon const m_debut,
                             maillon const m_fin) {
  maillon m = m_debut;
  fprintf(f, "[");
  while (m != m_fin) {
    fprintf(f, " %d", m->val);
    m = m->suivant;
  }
  fprintf(f, " %d ]", m->val);
}

/*!
 * Ajout d'un élément avant le maillon.
 * \param m maillon avant lequel on doit insérer.
 * \param _val valeur entière à insérer.
 */
static void maillon_ajouter_avant(maillon const m, int const _val) {
  maillon nouveau = maillon_creer(_val);
  nouveau->precedent = m->precedent;
  nouveau->suivant = m;
  m->precedent->suivant = nouveau;
  m->precedent = nouveau;
}

/*!
 * Ajout d'un élément après le maillon.
 * \param m maillon après lequel on doit insérer.
 * \param _val valeur entière à insérer.
 */
static void maillon_ajouter_apres(maillon const m, int const _val) {
  maillon nouveau = maillon_creer(_val);
  nouveau->suivant = m->suivant;
  nouveau->precedent = m;
  m->suivant->precedent = nouveau;
  m->suivant = nouveau;
}

/*!
 * Suppression du maillon d'avant s'il existe (c.-à-d. si la liste
 * correspondante ne contient qu'un maillon on ne fait rien).
 * \param m maillon avant lequel on doit supprimer.
 */
static void maillon_supprimer_avant(maillon const m) {
  if (!maillon_est_unique(m)) {
    maillon avant = m->precedent;
    avant->precedent->suivant = m;
    m->precedent = avant->precedent;
    free(avant);
  }
}

/*! suppression du maillon d'après s'il existe (c.-à-d. si la liste
 * correspondante ne contient qu'un maillon on ne fait rien).
 * \param m maillon après lequel on doit supprimer.
*/
static void maillon_supprimer_apres(maillon const m) {
  if (!maillon_est_unique(m)) {
    maillon apres = m->suivant;
    apres->suivant->precedent = m;
    m->suivant = apres->suivant;
    free(apres);
  }
}

/*!
 * Structure pour la liste en étendant la structure maillon.
 * Quand la liste est vide, il n'y a pas de liste circulaire (et les pointeurs
 * convernés valent NULL).
*/
struct liste_struct {
  unsigned int taille;
  maillon tete;
  maillon courant;
  maillon pied;
};

liste liste_creer(void) {
  liste l = malloc(sizeof(struct liste_struct));
  l->tete = NULL;
  l->courant = NULL;
  l->pied = NULL;
  return l;
}

void liste_detruire(liste *const l) {
  ASSERT_LISTE();
  maillon_detruire(&(*l)->tete);
  free(*l);
  *l = NULL;
}

/*!
 * Pour ajouter une valeur à une liste vide.
 * \param l liste où ajouter.
 * \param val valeur entière à jouter.
 */
static void liste_ajouter_a_vide(liste const l, int const val) {
  ASSERT_LISTE();
  maillon m = maillon_creer(val);
  l->tete = m;
  l->pied = m;
  l->taille = 1;
}

/*! Pour enlever la dernière valeur. */
static void liste_enlever_dernier(liste const l) {
  ASSERT_LISTE();
  maillon_detruire(&l->tete);
  l->tete = NULL;
  l->pied = NULL;
  l->taille = 0;
}

bool liste_est_vide(liste const l) {
  ASSERT_LISTE();
  return l->tete == NULL && l->courant == NULL && l->pied == NULL;
}

void liste_insertion_debut(liste const l, int const val) {
  ASSERT_LISTE();
  if (!liste_est_vide(l)) {
    maillon_ajouter_avant(l->tete, val);
    l->tete = l->tete->precedent;
    l->taille++;
  } else {
    liste_ajouter_a_vide(l, val);
  }
}

void liste_insertion_fin(liste const l, int const val) {
  ASSERT_LISTE();
  if (!liste_est_vide(l)) {
    maillon_ajouter_apres(l->pied, val);
    l->pied = l->pied->suivant;
    l->taille++;
  } else {
    liste_ajouter_a_vide(l, val);
  }
}

void liste_insertion_apres(liste const l, int const val) {
  ASSERT_LISTE();
  maillon_ajouter_apres(l->courant, val);
  l->taille++;
  if (l->courant == l->pied) {
    l->pied = l->courant->suivant;
  }
}

void liste_insertion_avant(liste const l, int const val) {
  ASSERT_LISTE();
  maillon_ajouter_avant(l->courant, val);
  l->taille++;
  if (l->courant == l->tete) {
    l->tete = l->courant->precedent;
  }
}

void liste_suppression_debut(liste const l) {
  ASSERT_LISTE();
  if (!liste_est_vide(l)) {
    maillon_supprimer_avant(l->tete->suivant);
    l->tete = l->pied->suivant;
    l->taille--;
  } else {
    liste_enlever_dernier(l);
  }
}

void liste_suppression_fin(liste const l) {
  ASSERT_LISTE();
  if (!liste_est_vide(l)) {
    maillon_supprimer_apres(l->pied->precedent);
    l->pied = l->tete->precedent;
    l->taille--;
  } else {
    liste_enlever_dernier(l);
  }
}

void liste_suppression_avant(liste const l) {
  ASSERT_LISTE();
  maillon_supprimer_avant(l->courant);
  l->taille--;
  if (l->courant == l->tete) {
    l->pied = l->tete->precedent;
  }
}

void liste_suppression_apres(liste const l) {
  ASSERT_LISTE();
  maillon_supprimer_apres(l->courant);
  l->taille--;
  if (l->courant == l->pied) {
    l->tete = l->pied->suivant;
  }
}

void liste_affichage(FILE *const f, liste const l) {
  assert(f != NULL);
  ASSERT_LISTE();
  fprintf(f, "Liste de %d éléments : ", l->taille);
  maillon_afficher(f, l->tete, l->pied);
}

void liste_courant_init(liste const l) {
  ASSERT_LISTE();
  l->courant = l->tete;
}

void liste_courant_suivant(liste const l) {
  ASSERT_LISTE_COURANT();
  l->courant = l->courant->suivant;
}

void liste_decalage(liste const l, int n) {
  ASSERT_LISTE_COURANT();
  for (int i = 0; i < n; i++) {
    l->courant = l->courant->suivant;
  }
}

int liste_taille(liste const l) {
  ASSERT_LISTE();
  return l->taille;
}

int liste_valeur_tete(liste const l) {
  ASSERT_LISTE();
  return l->tete->val;
}

int liste_valeur_pied(liste const l) {
  ASSERT_LISTE();
  return l->pied->val;
}

int liste_valeur_courant(liste const l) {
  ASSERT_LISTE_COURANT();
  return l->courant->val;
}

bool liste_est_tete(liste const l) {
  ASSERT_LISTE_COURANT();
  return l->courant == l->tete;
}

bool liste_est_pied(liste const l) {
  ASSERT_LISTE_COURANT();
  return l->courant == l->pied;
}
