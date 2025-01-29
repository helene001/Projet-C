#ifndef STRUCT_ETUD_H
#define STRUCT_ETUD_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define NOMBRE_TOURS 9
#define NOMBRE_LIGNES 7

typedef struct jeu Jeu;

typedef struct etudiant {
int type;
int pointsDeVie;
int PV_max;
int ligne;
int position;
int vitesse;
int degats;
int tour;
int un_sur_2; //permet de controller les évenements qui doivent arriver une fois sur 2 comme la vitesse du type d'Etudiant 'M' (avance si avancer_ou_non=1) ou les soins du type 'D'
struct etudiant* next;
struct etudiant* prev;
struct etudiant* next_line;
struct etudiant* prev_line;
} Etudiant;




Etudiant* creer_etu(int type,int ligne,int tour,Jeu* jeu,FILE* nom_fichier);
void placer(Jeu* jeu,FILE * nom_fichier);
void connecte_ligne(Jeu* jeu);
void type_Etudiant(int type,Etudiant* e,Jeu *j);
void liberer_etudiant(Jeu* j);
void touche_Etudiant(Etudiant *e, int degat_tourelle,int ligne,Jeu* jeu);
void avancer(Etudiant* e);
void afficher(Jeu *jeu);
Etudiant * trouver_ligne(Jeu * jeu,int ligne);
#endif
