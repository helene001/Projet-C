#ifndef STRUCT_ETUD_H
#define STRUCT_ETUD_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOMBRE_TOURS 9  
#define NOMBRE_LIGNES 7 
typedef struct etudiant {
int type;
int pointsDeVie;
int ligne;
int position;
int vitesse;
int degats;
int tour;
struct etudiant* next;
struct etudiant* next_line;
struct etudiant* prev_line;
} Etudiant;

typedef struct liste{
    Etudiant* tete;
    Etudiant* prochain; //prochain a apparaitre
    Etudiant* fin;

}Liste;

void creer_etu(int type,int ligne,int tour,Liste * l);
Liste* placer(FILE * nom_fichier);
void type_Etudiant(int type,Etudiant* e);
void liberer_liste(Liste *l);
void afficher_liste(Liste *l);
touche_Etudiant(Etudiant *e, int degat_tourelle,int ligne ,Liste *l);
#endif
