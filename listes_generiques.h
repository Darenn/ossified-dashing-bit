#ifndef LISTES_GENERIQUES
#define LISTES_GENERIQUES
#include <stdbool.h>
#include <stdio.h>

/*! \file
 * \brief Module liste générique.
 *
 * Les listes génériques sont codées dans une liste chaînée circulaire dont on
 * connaît la tête et le pied.
 * La taille de la liste est aussi enregistrée et n'est jamais recalculée.
 *
 * Afin de parcourir la liste, elle enregistre également une position courante.
 * Le parcours doit toujours être initialisé avant d'être utilisé.
 *
 * \copyright PASD
 * \version 2016
 */

/*!
 * Cette struture permet d'enregistrer une liste de valeurs.
 * Elle se base sur une autre structure assurant le chaînage et l'enregistrement
 * des valeurs.
 * Ces deux structures sont cachées et ne doivent jamais être manipulées
 * directement.
 */
typedef struct liste_struct *liste;

/*!
 * Création d'une liste vide.
 * \param _copie une fonction qui définit la valeur du maillon à partir d'une
 recopie.
 * \param _afficher une fonction qui définit comment on affiche la valeur du
 maillon.
 * \param _detruire une fonction qui définit comment désallouer la mémoire
                                 relative à la valeur du maillon
 * \return une nouvelle liste vide.
 */
liste liste_creer(void (*_copie)(void *val, void **pt),
                  void (*_afficher)(FILE *f, void *val),
                  void (*_detruire)(void **pt));

/*!
 * Destruction de la liste.
 * \param l pointeur vers la liste à détruire.
 */
void liste_detruire(liste *l);

/*!
 * Pour savoir si une liste est vide ou non.
 * \param l liste à tester.
 * \return true ssi la liste est vide.
 */
bool liste_est_vide(liste const l);

/*!
 * Insertion en début de liste.
 * À la sortie de la fonction, tete pointe désormais sur ce nouvel élément
 * (prendre en compte le cas de la liste vide).
 * \param l liste où insérer.
 * \param val pointeur vers la valeur à insérer.
 */
void liste_insertion_debut(liste l, void *val);

/*!
 * Insertion en fin de liste.
 * à la sortie de la fonction, pied pointe désormais sur ce nouvel élément
 * (prendre en compte le cas de la liste vide).
 * \param l liste où insérer.
 * \param val pointeur vers la valeur à insérer.
 */
void liste_insertion_fin(liste l, void *val);

/*!
 * Insertion après le maillon courant.
 * Si pied = courant alors pied doit être mis à jour.
 * \param l liste où insérer.
 * \param val pointeur vers la valeur à insérer.
 */
void liste_insertion_apres(liste l, void *val);

/*!
 * Insertion avant le maillon courant.
 * Si tete = courant alors tete doit être mis à jour .
 * \param l liste où insérer.
 * \param val un pointeur vers la valeur à insérer.
 */
void liste_insertion_avant(liste l, void *val);

/*!
 * Suppression de l'élément en tete de liste (mettre à jour tete).
 * \param l liste d'où supprimer.
 */
void liste_suppression_debut(liste l);

/*!
 * Suppression de l'élément en pied de liste (mettre à jour pied).
 * \param l liste d'où supprimer.
 */
void liste_suppression_fin(liste l);

/*!
 * Suppression de l'élément avant courant s'il existe (tete et pied doivent être
 * modifiés si nécessaire).
 * \param l liste d'où supprimer.
 */
void liste_suppression_avant(liste l);

/*!
 * Suppression de l'élément apres courant s'il existe (tete et pied doivent être
 * modifiés si nécessaire).
 * \param l liste d'où supprimer.
 */
void liste_suppression_apres(liste l);

/*!
 * Affichage des éléments de la liste.
 * Le résultat est de la forme (avec type entier):
 * \verbatim Liste de 5 éléments : [ -1 -3 10 15 20 ]\endverbatim
 * sans passage à la ligne à la fin.
 * \param f flux où imprimer.
 * \param l liste à afficher.
 */
void liste_affichage(FILE *f, liste l);

/*!
 * Initialise courant à tete.
 * Doit être appelé avant d'utiliser courant.
 * Doit être appelé sur une liste non vide.
 * \param l liste à parcourir.
 */
void liste_courant_init(liste l);

/*!
 * Passe courant sur l'élément suivant.
 * \param l liste parcourue.
 */
void liste_courant_suivant(liste l);

/*!
 * Décalage de courant de n positions.
 * Si n est négatif, il s'agit de décalage dans l'autre sens.
 * \param n nombre de décalage à faire.
 * \param l liste parcourue.
*/
void liste_decalage(liste l, int n);

/*!
 * Retourne la taille de la liste.
 * \param l liste sur laquelle porte la demande.
 * \return le nombre d'éléments dans la liste.
 */
unsigned int liste_taille(liste l);

/*!
 * Retourne la valeur de tete.
 * \param l liste sur laquelle porte la demande.
 * \return le nombre d'éléments dans la liste.
 */
void *liste_valeur_tete(liste l);

/*!
 * Retourne la valeur de pied.
 * \param l liste sur laquelle porte la demande.
 * \return la première valeur de la liste.
 */
void *liste_valeur_pied(liste l);

/*!
 * Retourne la valeur de courant.
 * \param l liste parcourue sur laquelle porte la demande.
 * \return la valeur de l'élément courant de la liste.
 */
void *liste_valeur_courant(liste l);

/*!
 * Retourne vrai si courant pointe sur tete.
 * \param l liste sur laquelle porte la demande.
 * \return true si la tete est l'élément courant.
 */
bool liste_est_tete(liste l);

/*!
 * Retourne vrai si courant pointe sur pied.
 * \param l liste sur laquelle porte la demande.
 * \return true si le pied est l'élément courant.
 */
bool liste_est_pied(liste l);

#endif
