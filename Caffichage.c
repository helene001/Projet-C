#include <stdio.h>
#include <stdlib.h>
#include "Caffichage.h"



//fontion qui affiche un terrain neutre
void afficheTerrainNeutre()
{
    for (int tour = 1; tour <= 9; tour++)
    {
        printf("Vague %d\n", tour);
        for (int i = 1; i <= 7; i++)
        {
            printf("%d|\t", i);
            for (int j = 1; j <= 15; j++)
            {
                printf(".\t");
            }
        printf("\n");
        }
    }
}

//fonction qui affiche les vagues AVANT le debut du jeu
void afficheVagues(FILE* fichierVague)
{
    //remplir le tableau de points 
    char affichage[7][15]; //7 lignes et 15 colonnes
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 15; j++)
            affichage[i][j] = '.';
    }
    
    
    int numeroTour = 0;
    int numeroLigne = 0;
    char typeFichier = 0; 
    char chaine[100] = "";

    //transforme le fichier en l'affichage souhaite
    do
    {
    fscanf(fichierVague, "%d %d %c", &numeroTour, &numeroLigne, &typeFichier);
    affichage[numeroLigne-1][numeroTour-1] = typeFichier;
    } while (fgets(chaine, 100, fichierVague) != NULL);
    
    //afficher le tableau final
    for (int i = 0; i < 7; i++)
    {
        printf("%d|", i+1);
        for (int j = 0; j < 15; j++)
            printf("%c\t", affichage[i][j]);
        printf("\n");
    }

}


