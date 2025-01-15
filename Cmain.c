#include <stdio.h>
#include <stdlib.h>
#include "Caffichage.h"
#define TAILLE_MAX 100

int main(int argc, char* argv[])
{
    FILE* fichierVague = NULL;
    fichierVague = fopen("ex_vague.txt", "r");
    char cagnotte[TAILLE_MAX]= "";

    int ligneFichier[2] = {0};
    char typeFichier = 0; 

    if (fichierVague != NULL)
    {
        //gestion cagnotte
        fgets(cagnotte, TAILLE_MAX, fichierVague);
        printf("Credit restant : %s\n", cagnotte);
        
        //gestion placement final (= affichage des vagues AVANT le debut du jeu)
        fscanf(fichierVague, "%d %d %c", &ligneFichier[0], &ligneFichier[1], &typeFichier);
        printf("Ligne 1 : %d %d %c\n", ligneFichier[0], ligneFichier[1], typeFichier);

        afficheTerrainNeutre();
        fclose(fichierVague);
    }
    else
    {
        printf("Erreur");
    }
    return 0;
}