#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define NOMBRE_TOURS 9
#define NOMBRE_LIGNES 7
#define NOMBRE_POSITIONS 15

typedef struct jeu Jeu;

typedef struct tourelle {
    int type;               // Type de la tourelle
    int pointsDeVie;        // Points de vie de la tourelle
    int ligne;              // Ligne de la tourelle
    int position;           // Position de la tourelle
    int prix;               // Coût de la tourelle
    struct tourelle *next;  // Pointeur vers la tourelle suivante
} Tourelle;


// =====================================
//          Fonctions Tourelles
// =====================================

//      Création de Tourelle
Tourelle *creerTourelle(int ligne, int position, int type,Jeu* jeu);

//      Contact Tourelles
/*
void contactTourelles(Jeu *jeu);

//      Attaque Tourelles
void attaquerLigne(Jeu *jeu, Tourelle *tourelle);

//      Ralentire Tourelles
void ralentirEnnemi(Jeu *jeu, Tourelle *tourelle);

//      Action Tourelles
void actionsTourelles(Jeu *jeu);

//      Attaquer Zone
void attaquerZone(Jeu *jeu, Tourelle *tourelle);
*/
void chainage_tourelle(Jeu * jeu);
