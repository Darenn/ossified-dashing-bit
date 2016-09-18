#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "listes_generiques.h"

void copie_int(void* val, void** pt)
{
  *pt = (int*)malloc(sizeof(int));
  memcpy(*pt,val,sizeof(int));
}

void afficher_int(FILE* f, void* val)
{
  fprintf(f,"%d ",*((int*)(val)));
}

void detruire_int(void **pt)
{
  if (*pt != NULL) {
    free(*pt);
    (*pt) = NULL;
  }
}
void test1(FILE* f_out)
{
  fprintf(f_out,"-----------------test1------------------\n");
  liste *l = liste_creer(&copie_int, &afficher_int, &detruire_int);
  int a = 1;
  liste_insertion_debut(l,&a);
  liste_affichage(f_out,l);
  fprintf(f_out,"\n");
  liste_detruire(&l);
}

void test2(FILE* f_out)
{
  fprintf(f_out,"-----------------test2------------------\n");
  liste *l = liste_creer(&copie_int, &afficher_int, &detruire_int);
  int a = 3;
  liste_insertion_fin(l,&a);
  liste_affichage(f_out,l);
  fprintf(f_out,"\n");
  liste_detruire(&l);
}

void test3(FILE* f_out)
{
  fprintf(f_out,"-----------------test3------------------\n");
  liste *l = liste_creer(&copie_int, &afficher_int, &detruire_int);
  int a = 1;
  liste_insertion_debut(l,&a);
  a = 2;
  liste_insertion_debut(l,&a);
  a = 3;
  liste_insertion_fin(l,&a);
  a = 4;
  liste_insertion_fin(l,&a);    
  liste_courant_init(l);
  a = 10;
  liste_insertion_apres(l,&a);
  liste_affichage(f_out,l);
  fprintf(f_out,"\n");
  liste_detruire(&l);
}

void test4(FILE* f_out)
{
  fprintf(f_out,"-----------------test4------------------\n");
  
  FILE* f_in = fopen("test_in.txt","r");  
  
  liste *l = liste_creer(&copie_int, &afficher_int, &detruire_int); 
  int a;
  fscanf(f_in,"%d",&a);
  liste_insertion_debut(l,&a);
  fscanf(f_in,"%d",&a);
  liste_insertion_fin(l,&a);
  fscanf(f_in,"%d",&a);
  liste_insertion_fin(l,&a);
  fscanf(f_in,"%d",&a);
  liste_insertion_fin(l,&a);
  fscanf(f_in,"%d",&a);
  liste_insertion_fin(l,&a);
  fscanf(f_in,"%d",&a);
  liste_insertion_debut(l,&a);
  fscanf(f_in,"%d",&a);
  liste_insertion_debut(l,&a);
  fscanf(f_in,"%d",&a);
  liste_insertion_debut(l,&a);
  liste_suppression_debut(l);
  liste_suppression_debut(l);
  liste_suppression_fin(l);
  fscanf(f_in,"%d",&a);
  liste_courant_init(l);
  liste_courant_suivant(l);
  liste_insertion_avant(l,&a);
  fscanf(f_in,"%d",&a);
  liste_insertion_avant(l,&a);
  fscanf(f_in,"%d",&a);
  liste_insertion_apres(l,&a);
  fscanf(f_in,"%d",&a);
  liste_insertion_apres(l,&a);
  liste_courant_suivant(l);
  liste_suppression_avant(l);
  liste_suppression_apres(l);
  liste_suppression_avant(l);
  liste_suppression_apres(l);
  liste_affichage(f_out,l);
  fprintf(f_out,"\n");
  liste_courant_init(l);
  while(!liste_est_pied(l)) {
    if (liste_est_tete(l))
      fprintf(f_out,"tete : %d\n",*(int*)(liste_valeur_courant(l)));
    else
      fprintf(f_out,"courant : %d\n",*(int*)(liste_valeur_courant(l)));
    liste_courant_suivant(l);
  }
  fprintf(f_out,"pied : %d\n",*(int*)liste_valeur_pied(l));
  fclose(f_in);
  liste_detruire(&l);
}

void test5(FILE* f_out)
{
  fprintf(f_out,"-----------------test5------------------\n");
  
  FILE* f_in = fopen("test_in.txt","r");  
  
  liste *l = liste_creer(&copie_int, &afficher_int, &detruire_int); 
  
  int a;
  fscanf(f_in,"%d",&a);  
  liste_insertion_debut(l,&a);
  fscanf(f_in,"%d",&a);
  do {
    liste_insertion_avant(l,&a);
    fscanf(f_in,"%d",&a);
  }  while (!feof(f_in)) ;
  
  liste_affichage(f_out,l);
  fprintf(f_out,"\n");
  liste_detruire(&l);
  fclose(f_in);
  
}

int main (void)
{

  FILE* f_out = fopen("test_out.txt","w");
  test1(f_out);
  test2(f_out);
  test3(f_out);
  test4(f_out);
  test5(f_out);
  fclose(f_out);


  return 0 ;
}
