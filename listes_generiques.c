#include "listes_generiques.h"
#include <assert.h>
#include <stdio.h>
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

/*! \brief Un maillon est un pointeur sur (référence vers) une struct
 * maillon_struct .
 */
typedef struct maillon_struct *maillon;

/*!
 * \brief Structure servant à définir un élément du type de la valeur de la
 * liste.
 * Cette structure n'est visible que depuis listes_generiques.c .
 * Les fonctions attenantes sont static pour être également masquées. */
struct maillon_struct {
  void *val;
  maillon suivant;
  maillon precedent;
};

/*!
 * \brief Création d'un maillon dont la valeur est val .
 * suivant et precedent doivent pointer sur ce maillon.
 * \param val un pointeur vers la valeur à stocker dans le maillon.
 * \param copier un pointeur vers une fonction qui définit la valeur du maillon
 * à partir d'une recopie.
 * \return nouveau maillon stockant val et bouclant sur lui-même.
 */
static maillon maillon_creer(void *val, void (*copier)(void *val, void **pt)) {
  assert(copier != NULL && val != NULL);
  maillon m = malloc(sizeof(struct maillon_struct));
  copier(val, &(m->val));
  m->precedent = m->suivant = m;
  return m;
}

/*!
 * \brief Test pour savoir si le maillon est unique ( bouclant sur lui-même et
 * correspondant à une liste de taille 1 ).
 * \param m maillon à tester.
 */
static bool maillon_est_unique(maillon m) {
  assert(m != NULL);
  return m == m->precedent && m == m->suivant;
}

/*!
 * \brief Destruction de toute la liste chaînée.
 * \param m pointeur sur un maillon de la liste chaînée à détruire.
 * \param detruire une pointeur vers une fonction qui définit comment désallouer
 * la mémoire relative à la valeur du maillon
*/
static void maillon_detruire(maillon *m, void (*detruire)(void **pt)) {
  assert(detruire != NULL);
  assert(m != NULL && *m != NULL);
  maillon start = *m;
  maillon courant = (*m)->suivant;
  maillon suivant;
  while (courant != start) {
    suivant = courant->suivant;
    detruire(&(courant->val));
    free(courant);
    courant = suivant;
  }
  detruire(&(courant->val));
  free(courant);
  *m = NULL;
}

/*!
 * \brief Affichage d'un ensemble de maillon à partir d'un début et d'une fin.
 * Le résultat est de la forme \verbatim[ 1 2 3 ]\endverbatim sans saut de
 * ligne.
 * \param f flux où imprimer.
 * \param m_debut premier maillon à imprimer.
 * \param m_fin dernier maillon à imprimer.
 * \param afficher un pointeur vers une fonction qui définit comment on affiche
 * la valeur du maillon.
 */
static void maillon_afficher(FILE *const f, maillon m_debut, maillon m_fin,
                             void (*afficher)(FILE *f, void *val)) {
  assert(afficher != NULL && f != NULL && m_debut != NULL && m_fin != NULL);
  maillon m = m_debut;
  fprintf(f, "[ ");
  while (m != m_fin) {
    afficher(f, m->val);
    m = m->suivant;
  }
  afficher(f, m->val);
  fprintf(f, "]");
}

/*!
 * \brief Ajout d'un élément avant le maillon.
 * \param m maillon avant lequel on doit insérer.
 * \param _val un pointeur vers la valeur entière à insérer.
 * \param copier un pointeur vers une fonction qui définit la valeur du maillon
 * à partir d'une recopie.
 */
static void maillon_ajouter_avant(maillon m, void *_val,
                                  void (*copier)(void *val, void **pt)) {
  assert(m != NULL);
  assert(_val != NULL);
  assert(copier != NULL);
  maillon nouveau = maillon_creer(_val, copier);
  nouveau->precedent = m->precedent;
  nouveau->suivant = m;
  m->precedent->suivant = nouveau;
  m->precedent = nouveau;
}

/*!
 * \brief Ajout d'un élément après le maillon.
 * \param m maillon après lequel on doit insérer.
 * \param _val un pointeur vers la valeur entière à insérer.
 * \param copier un pointeur vers une fonction qui définit la valeur du maillon
 */
static void maillon_ajouter_apres(maillon m, void *_val,
                                  void (*copier)(void *val, void **pt)) {
  assert(m != NULL && _val != NULL && copier != NULL);
  maillon nouveau = maillon_creer(_val, copier);
  nouveau->suivant = m->suivant;
  nouveau->precedent = m;
  m->suivant->precedent = nouveau;
  m->suivant = nouveau;
}

/*!
* \brief Suppression du maillon d'avant s'il existe (c.-à-d. si la liste
* correspondante ne contient qu'un maillon on ne fait rien).
* \param m maillon avant lequel on doit supprimer.
* \param copier un pointeur vers une fonction qui définit comment désallouer la
* mémoire relative à la valeur du maillon
*/
static void maillon_supprimer_avant(maillon m, void (*detruire)(void **pt)) {
  assert(m != NULL && detruire != NULL);
  if (!maillon_est_unique(m)) {
    maillon avant = m->precedent;
    avant->precedent->suivant = m;
    m->precedent = avant->precedent;
    detruire(&(avant->val));
    free(avant);
  }
}

/*! \brief suppression du maillon d'après s'il existe (c.-à-d. si la liste
 * correspondante ne contient qu'un maillon on ne fait rien).
 * \param m maillon après lequel on doit supprimer.
 * \param copier un pointeur vers une fonction qui définit comment désallouer la
 * mémoire relative à la valeur du maillon
*/
static void maillon_supprimer_apres(maillon m, void (*detruire)(void **pt)) {
  assert(m != NULL && detruire != NULL);
  if (!maillon_est_unique(m)) {
    maillon apres = m->suivant;
    apres->suivant->precedent = m;
    m->suivant = apres->suivant;
    detruire(&(apres->val));
    free(apres);
  }
}

/* \brief la structure définit 3 champs supplémentaires qui sont des pointeurs
 * sur fonction.
 */
struct liste_struct {
  unsigned int taille;
  maillon tete;
  maillon pied;
  maillon courant;
  void (*copier)(
      void *val,
      void **pt); /* pour définir la valeur du maillon à partir d'une recopie */
  void (*afficher)(
      FILE *f,
      void *val); /* pour définir comment on affiche la valeur du maillon */
  void (*detruire)(void **pt); /* pour définir comment désallouer la mémoire
                                  relative à la valeur du maillon */
};

liste liste_creer(void (*_copier)(void *val, void **pt),
                  void (*_afficher)(FILE *f, void *val),
                  void (*_detruire)(void **pt)) {
  assert(_copier != NULL && _afficher != NULL && _detruire != NULL);
  liste l = malloc(sizeof(struct liste_struct));
  l->tete = NULL;
  l->courant = NULL;
  l->pied = NULL;
  l->copier = _copier;
  l->afficher = _afficher;
  l->detruire = _detruire;
  return l;
}

void liste_detruire(liste *l) {
  ASSERT_LISTE();
  maillon_detruire(&(*l)->tete, (*l)->detruire);
  free(*l);
  *l = NULL;
}

/*!
 * \brief Pour ajouter une valeur à une liste vide.
 * \param l liste où ajouter.
 * \param val valeur entière à jouter.
 */
static void liste_ajouter_a_vide(liste const l, int *const val) {
  ASSERT_LISTE();
  assert(val != NULL);
  maillon m = maillon_creer(val, l->copier);
  l->tete = m;
  l->pied = m;
  l->taille = 1;
}

/*! \brief Pour enlever la dernière valeur. */
static void liste_enlever_dernier(liste const l) {
  ASSERT_LISTE();
  maillon_detruire(&l->tete, l->detruire);
  l->tete = NULL;
  l->pied = NULL;
  l->taille = 0;
}

bool liste_est_vide(liste const l) {
  ASSERT_LISTE();
  return l->tete == NULL && l->courant == NULL && l->pied == NULL;
}

void liste_insertion_debut(liste l, void *val) {
  ASSERT_LISTE();
  assert(val != NULL);
  if (!liste_est_vide(l)) {
    maillon_ajouter_avant(l->tete, val, l->copier);
    l->tete = l->tete->precedent;
    l->taille++;
  } else {
    liste_ajouter_a_vide(l, val);
  }
}

void liste_insertion_fin(liste l, void *val) {
  ASSERT_LISTE();
  assert(val != NULL);
  if (!liste_est_vide(l)) {
    maillon_ajouter_apres(l->pied, val, l->copier);
    l->pied = l->pied->suivant;
    l->taille++;
  } else {
    liste_ajouter_a_vide(l, val);
  }
}

void liste_insertion_avant(liste l, void *val) {
  ASSERT_LISTE_COURANT();
  assert(val != NULL);
  maillon_ajouter_avant(l->courant, val, l->copier);
  l->taille++;
  if (l->courant == l->tete) {
    l->tete = l->courant->precedent;
  }
}

void liste_insertion_apres(liste l, void *val) {
  ASSERT_LISTE_COURANT();
  assert(val != NULL);
  maillon_ajouter_apres(l->courant, val, l->copier);
  l->taille++;
  if (l->courant == l->pied) {
    l->pied = l->courant->suivant;
  }
}

void liste_suppression_debut(liste l) {
  ASSERT_LISTE();
  if (liste_taille(l) >= 2) {
    maillon_supprimer_avant(l->tete->suivant, l->detruire);
    l->tete = l->pied->suivant;
    l->taille--;
  } else {
    liste_enlever_dernier(l);
  }
}

void liste_suppression_fin(liste l) {
  ASSERT_LISTE();
  if (liste_taille(l) >= 2) {
    maillon_supprimer_apres(l->pied->precedent, l->detruire);
    l->pied = l->tete->precedent;
    l->taille--;
  } else {
    liste_enlever_dernier(l);
  }
}

void liste_suppression_avant(liste l) {
  ASSERT_LISTE_COURANT();
  assert(l->courant != NULL);
  if (liste_taille(l) >= 2) {
    maillon_supprimer_avant(l->courant, l->detruire);
    l->taille--;
    if (l->courant == l->tete) {
      l->pied = l->tete->precedent;
    }
  } else {
    liste_enlever_dernier(l);
  }
}

void liste_suppression_apres(liste l) {
  ASSERT_LISTE_COURANT();
  assert(l->courant != NULL);
  if (liste_taille(l) >= 2) {
    maillon_supprimer_apres(l->courant, l->detruire);
    l->taille--;
    if (l->courant == l->pied) {
      l->tete = l->pied->suivant;
    }
  } else {
    liste_enlever_dernier(l);
  }
}

void liste_affichage(FILE *f, liste l) {
  assert(f != NULL);
  ASSERT_LISTE();
  fprintf(f, "Liste de %d éléments : ", l->taille);
  maillon_afficher(f, l->tete, l->pied, l->afficher);
}

void liste_decalage(liste l, int n) {
  ASSERT_LISTE_COURANT();
  for (int i = 0; i < n; i++) {
    l->courant = l->courant->suivant;
  }
}

unsigned int liste_taille(liste l) {
  ASSERT_LISTE();
  return l->taille;
}

// TODO assert ?
void *liste_valeur_tete(liste l) {
  ASSERT_LISTE();
  return l->tete->val;
}

void *liste_valeur_pied(liste l) {
  ASSERT_LISTE();
  return l->pied->val;
}

void *liste_valeur_courant(liste l) {
  ASSERT_LISTE_COURANT();
  return l->courant->val;
}

bool liste_est_tete(liste l) {
  ASSERT_LISTE_COURANT();
  return l->courant == l->tete;
}

bool liste_est_pied(liste l) {
  ASSERT_LISTE_COURANT();
  return l->courant == l->pied;
}

void liste_courant_init(liste l) {
  ASSERT_LISTE();
  l->courant = l->tete;
}

void liste_courant_suivant(liste l) {
  ASSERT_LISTE_COURANT();
  l->courant = l->courant->suivant;
}
