#include <stdio.h>
#include <stdlib.h>
#include "Caffichage.h"
#include "struct_etud.h"
#include "struct_jeu.h"
#include "Tourelle.h"
#include <time.h>
#include <string.h>
#define TAILLE_MAX 100
//#define Fichier_vague ... a faire quand on aura plusieurs mode de jeu pour bonne gestion memoire en cas d 'erreur
int main(int argc, char* argv[])
{
    FILE* fichierVague = NULL;
    fichierVague = fopen("ex_vague.txt", "r");
    
    char cagnotte[TAILLE_MAX]= "";
 
    if ((fichierVague != NULL) && (fichierConforme(fichierVague)))
    {
        //gestion cagnotte
        fgets(cagnotte, TAILLE_MAX, fichierVague);
        printf("Credit restant : %s\n", cagnotte);
        
        //afficher les vagues AVANT le debut du jeu
        afficheVagues(fichierVague);
        rewind(fichierVague);
        /*on initialise jeu*/
        Jeu* jeu=malloc(sizeof(Jeu));
        jeu->tour=0;
        jeu->cagnotte=atoi(cagnotte);
        jeu->tourelles=NULL;
        jeu->derniere=NULL;
        jeu->etudiants=NULL;
        jeu->dernier=NULL;
        //on chaine les étudiants
        placer(jeu,fichierVague);
        fclose(fichierVague);
        //on chaine les étudiants par rapport a leurs lignes
        connecte_ligne(jeu);
        //on chaine les tourelles
        chainage_tourelle(jeu);
        //on lance le jeu
        affichejeu(jeu);
    }
    else
    {
        fclose(fichierVague);
        printf("Erreur.\n");
    }
    return 0;
}
