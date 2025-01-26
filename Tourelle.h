#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOMBRE_TOURS 9
#define NOMBRE_LIGNES 7
#define NOMBRE_POSITIONS 15       

// Types de tourelles
#define TOURRELE_DE_BASE 1
#define TOURRELE_RALENTISSEUR 2
#define TOURRELE_MINE 3
#define TOURRELE_ZONE 4
#define TOURRELE_MUR 5


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
Tourelle *creerTourelle(int ligne, int position, int type);

//      Contact Tourelles
void contactTourelles(Jeu *jeu);

//      Attaque Tourelles
void attaquerLigne(Jeu *jeu, Tourelle *tourelle);

//      Ralentire Tourelles
void ralentirEnnemi(Jeu *jeu, Tourelle *tourelle);

//      Action Tourelles
void actionsTourelles(Jeu *jeu);

//      Attaquer Zone
void attaquerZone(Jeu *jeu, Tourelle *tourelle);
