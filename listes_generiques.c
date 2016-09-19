#include "listes_generiques.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*! \file
 * \brief La documentation pour les parties (types, variables, fonctions…)
 * internes du modules sont documentées ici.
 *
 * \copyright PASD
 * \version 2016
 */

/*! Un maillon est un pointeur sur (référence vers) une struct maillon_struct .
 */
typedef struct maillon_struct *maillon;

/*!
 * Structure servant à définir un élément du type de la valeur de la liste.
 * Cette structure n'est visible que depuis listes_generiques.c .
 * Les fonctions attenantes sont static pour être également masquées. */
struct maillon_struct {
  void *val;
  maillon suivant;
  maillon precedent;
};

/* les définitions des fonctions sont identiques que pour la liste des entiers*/
/* Mais certaines nécessitent un paramètre supplémentaire la fonction copier */
/* afficher ou detruire qui permettent de rendre générique la liste */
/* Pour l'essentiel il s'agit de reprendre les fonctions pour les listes */
/* d'entiers et de les adapter à la généricité */

/*!
 * Création d'un maillon dont la valeur est val .
 * suivant et precedent doivent pointer sur ce maillon.
 * \param val un pointeur vers la valeur à stocker dans le maillon.
 * \param copier un pointeur vers une fonction qui définit la valeur du maillon
 * à partir d'une recopie.
 * \return nouveau maillon stockant val et bouclant sur lui-même.
 */
static maillon maillon_creer(void *val, void (*copier)(void *val, void **pt)) {
  maillon m = malloc(sizeof(struct maillon_struct));
  copier(val, &m->val);
  m->precedent = m->suivant = m;
  return m;
}

/*!
 * Test pour savoir si le maillon est unique ( bouclant sur lui-même et
 * correspondant à une liste de taille 1 ).
 * \param m maillon à tester.
 */
static bool maillon_est_unique(maillon m) {
  return m == m->precedent & m == m->suivant;
}

/*!
 * Destruction de toute la liste chaînée.
 * \param m (pointeur sur un) maillon de la liste chaînée à détruire.
*/
static void maillon_detruire(maillon *m, void (*detruire)(void **pt)) {}

/*!
 * Affichage d'un ensemble de maillon à partir d'un début et d'une fin.
 * Le résultat est de la forme \verbatim[ 1 2 3 ]\endverbatim sans saut de
 * ligne.
 * \param f flux où imprimer.
 * \param m_debut premier maillon à imprimer.
 * \param m_fin dernier maillon à imprimer.
 * \param afficher un pointeur vers une fonction qui définit comment on affiche
 * la valeur du maillon.
 */
static void maillon_afficher(FILE *f, maillon m_debut, maillon m_fin,
                             void (*afficher)(FILE *f, void *val)) {}

/*!
 * Ajout d'un élément avant le maillon.
 * \param m maillon avant lequel on doit insérer.
 * \param _val un pointeur vers la valeur entière à insérer.
 * \param copier un pointeur vers une fonction qui définit la valeur du maillon
 * à partir d'une recopie.
 */
static void maillon_ajouter_avant(maillon m, void *_val,
                                  void (*copier)(void *val, void **pt)) {}

/*!
 * Ajout d'un élément après le maillon.
 * \param m maillon après lequel on doit insérer.
 * \param _val un pointeur vers la valeur entière à insérer.
 * \param copier un pointeur vers une fonction qui définit la valeur du maillon
 */
static void maillon_ajouter_apres(maillon m, void *_val,
                                  void (*copier)(void *val, void **pt)) {}

/*!
* Suppression du maillon d'avant s'il existe (c.-à-d. si la liste
* correspondante ne contient qu'un maillon on ne fait rien).
* \param m maillon avant lequel on doit supprimer.
* \param copier un pointeur vers une fonction qui définit comment désallouer la
* mémoire relative à la valeur du maillon
*/
static void maillon_supprimer_avant(maillon m, void (*detruire)(void **pt)) {}

/*! suppression du maillon d'après s'il existe (c.-à-d. si la liste
 * correspondante ne contient qu'un maillon on ne fait rien).
 * \param m maillon après lequel on doit supprimer.
 * \param copier un pointeur vers une fonction qui définit comment désallouer la
 * mémoire relative à la valeur du maillon
*/
static void maillon_supprimer_apres(maillon m, void (*detruire)(void **pt)) {}

/* la structure définit 3 champs supplémentaires qui sont des pointeurs sur
 * fonction*/
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
  liste ls = malloc(sizeof(struct liste_struct));
}

void liste_detruire(liste *l) {}

void liste_insertion_debut(liste l, void *val) {}

void liste_insertion_fin(liste l, void *val) {}

void liste_insertion_avant(liste l, void *val) {}

void liste_insertion_apres(liste l, void *val) {}

void liste_suppression_debut(liste l) {}

void liste_suppression_fin(liste l) {}

void liste_suppression_avant(liste l) {}

void liste_suppression_apres(liste l) {}

void liste_affichage(FILE *f, liste l) {}

void liste_decalage(liste l, int n) {}

unsigned int liste_taille(liste l) {}

void *liste_valeur_tete(liste l) {}

void *liste_valeur_pied(liste l) {}

void *liste_valeur_courant(liste l) {}

bool liste_est_tete(liste l) {}

bool liste_est_pied(liste l) {}

void liste_courant_init(liste l) {}

void liste_courant_suivant(liste l) {}
