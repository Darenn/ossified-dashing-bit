#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "listes_int.h"


/*! \file
 * \brief La documentation pour les parties (types, variables, fonctions…) internes du modules sont documentées ici.
 *
 * \copyright PASD
 * \version 2016
 */


/*!
 * Structure servant à définir un élément de type int de la liste.
 * Cette structure n'est visible que depuis listes_int.c .
 * Les fonctions attenantes sont static pour être également masquées. */
struct maillon_struct {
} ;


/*! Un maillon est un pointeur sur (référence vers) une struct maillon_struct . */
typedef struct maillon_struct * maillon;


/*!
 * Création d'un maillon dont la valeur est _val .
 * suivant et precedent doivent pointer sur ce maillon.
 * \param _val valeur à stocker dans le maillon.
 * \return nouveau maillon stockant _val et bouclant sur lui-même.
 */
static maillon maillon_creer ( int const _val ) {
}


/*!
 * Test pour savoir si le maillon est unique ( bouclant sur lui-même et correspondant à une liste de taille 1 ).
 * \param m maillon à tester.
 */
static bool maillon_est_unique ( maillon const m ) {
}


/*! 
 * Destruction de toute la liste chaînée.
 * \param m (pointeur sur un) maillon de la liste chaînée à détruire.
*/
static void maillon_detruire ( maillon * const m ) {
}


/*! 
 * Affichage d'un ensemble de maillon à partir d'un début et d'une fin.
 * Le résultat est de la forme \verbatim[ 1 2 3 ]\endverbatim sans saut de ligne.
 * \param f flux où imprimer.
 * \param m_debut premier maillon à imprimer. 
 * \param m_fin dernier maillon à imprimer. 
 */
static void maillon_afficher ( FILE * const f ,
			       maillon const m_debut ,
			       maillon const m_fin ) {
}


/*!
 * Ajout d'un élément avant le maillon.
 * \param m maillon avant lequel on doit insérer.
 * \param _val valeur entière à insérer.
 */
static void maillon_ajouter_avant ( maillon const m ,
				    int const _val ) {
}


/*!
 * Ajout d'un élément après le maillon.
 * \param m maillon après lequel on doit insérer.
 * \param _val valeur entière à insérer.
 */
static void maillon_ajouter_apres ( maillon const m ,
				    int const _val ) {
}


/*! 
 * Suppression du maillon d'avant s'il existe (c.-à-d. si la liste correspondante ne contient qu'un maillon on ne fait rien).
 * \param m maillon avant lequel on doit supprimer.
 */
static void maillon_supprimer_avant ( maillon const m ) {
}


/*! suppression du maillon d'après s'il existe (c.-à-d. si la liste correspondante ne contient qu'un maillon on ne fait rien).
 * \param m maillon après lequel on doit supprimer.
*/
static void maillon_supprimer_apres ( maillon const m ) {
}


/*! 
 * Structure pour la liste en étendant la structure maillon. 
 * Quand la liste est vide, il n'y a pas de liste circulaire (et les pointeurs convernés valent NULL). 
*/
struct liste_struct {
};


liste liste_creer ( void ) {
}


void liste_detruire ( liste * const l ) {
}


/*!
 * Pour ajouter une valeur à une liste vide.
 * \param l liste où ajouter.
 * \param val valeur entière à jouter.
 */
static void liste_ajouter_a_vide ( liste const l ,
				   int const val ) {
}


/*! Pour enlever la dernière valeur. */
static void liste_enlever_dernier ( liste const l ) {
}


bool liste_est_vide ( liste const l ) {
}


void liste_insertion_debut ( liste const l ,
			     int const val ) {
}


void liste_insertion_fin ( liste const l ,
			   int const val ) {
}


void liste_insertion_apres ( liste const l ,
			     int const val ) {
}


void liste_insertion_avant ( liste const l ,
			     int const val ) {
}


void liste_suppression_debut ( liste const l ) {
}


void liste_suppression_fin ( liste const l ) {
}


void liste_suppression_avant ( liste const l ) {
}


void liste_suppression_apres ( liste const l ) {
}


void liste_affichage ( FILE * const f ,
		       liste const l ) {
}


void liste_courant_init ( liste const l ) {
}


void liste_courant_suivant ( liste const l ) {
}


void liste_decalage ( liste const l ,
		      int n ) {
}


int liste_taille ( liste const l ) {
}


int liste_valeur_tete ( liste const l ) {
}


int liste_valeur_pied ( liste const l ) {
}


int liste_valeur_courant ( liste const l ) {
}


bool liste_est_tete ( liste const l ) {
}


bool liste_est_pied ( liste const l ) {
}


