
#ifndef TOURELLE_H
#define TOURELLE_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#define NOMBRE_POSITIONS 15

typedef struct jeu Jeu;
typedef struct etudiant Etudiant;
typedef struct tourelle {
    int type;
    int pointsDeVie;
    int ligne;
    int position;
    int prix;
    int degats;
    struct tourelle *next;  // Pointeur vers la tourelle suivante
} Tourelle;


// =====================================
//          Fonctions Tourelles
// =====================================

//      Création de Tourelle
Tourelle *creerTourelle(int ligne, int position, int type,Jeu* jeu);

//      Contact Tourelles

//void contactTourelles(Jeu *jeu);

//      Attaque Tourelles
void attaquerT(Jeu *jeu, Tourelle *tourelle);

//      Ralentire Tourelles
void ralentirEnnemi(Jeu *jeu, Tourelle *tourelle);

//      Action Tourelles
void actionsTourelles(Jeu *jeu);

//      Attaquer Zone
void attaquerZone(Jeu *jeu, Tourelle *tourelle);

void chainage_tourelle(Jeu * jeu);

void toucher_Tourelle(Jeu *jeu,Tourelle* tourelle,int degat);

Tourelle *trouver_pos_exacte_tour(Jeu* jeu,int ligne ,int pos);


void liberer_tourelle(Jeu* j);


#endif
