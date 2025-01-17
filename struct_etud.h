#ifndef STRUCT_ETUD_H
#define STRUCT_ETUD_H
#include <stdio.h>
#include <stdlib.h>

#define NOMBRE_TOURS 9  
#define NOMBRE_LIGNES 7 
typedef struct etudiant {
int type;
int pointsDeVie;
int ligne;
int position;
int vitesse;
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

#endif
