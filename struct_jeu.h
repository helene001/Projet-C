#ifndef STRUCT_JEU_H
#define STRUCT_JEU_H


#include <stdio.h>
#include <stdlib.h>


typedef struct etudiant Etudiant;
typedef struct jeu{ 
    //Tourelle* tourelles; 
    Etudiant* etudiants; 
    Etudiant* dernier;
    int cagnotte; 
    int tour; 
    } Jeu;


#endif
