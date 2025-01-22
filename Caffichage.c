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


// fonction qui affiche les vagues pendant le jeu (1 par 1 avec les PV)
void afficheVagues2(FILE* fichierVague)
{
    //remplir le tableau de points
    char affichage[7][30]; // 7 lignes et 30 colonnes pour observer l'avancee des etudiants
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 30; j++)
            affichage[i][j] = '.';
    }

    int numeroTour = 0;
    int numeroLigne = 0;
    char typeFichier = 0;
    char chaine[100] = "";

    // transforme le fichier en l'affichage souhaite dans un tableau de 30 colonnes
    do
    {
        fscanf(fichierVague, "%d %d %c", &numeroTour, &numeroLigne, &typeFichier);
        affichage[numeroLigne - 1][14 + numeroTour] = typeFichier; //la vague commence a la 15e colonne pour la voir apparaitre progressivement OU START A LA COLONNE 16 CA FACILITE LES CHOSES PR PV AVANCER AP
        //printf("%c\n", affichage[numeroLigne-1][15-numeroTour]);
      
    } while (fgets(chaine, 100, fichierVague) != NULL);


    // afficher le tableau final
    for (int i = 0; i < 7; i++)
    {
        printf("%d| ", i + 1);
        for (int j = 0; j < 25; j++)
            printf("%c  ", affichage[i][j]);
        printf("\n");
    }
    //c'est BON till that
    

    // afficher les tours sucessifs (observation des etudiants qui avancent)
    //etapes : 1) avance, 2) print le tour (d'abord on avance de rien) et on le fait 9 = numeroTour fois
        for (int tour = 1; tour <= numeroTour; tour++)
        {
            printf("Tour %d\n", tour);
            //faire avancer les etudiants A FAIRE !!
            for (int i = 0; i < 7; i++)
            {
                {
                    affichage[i][14] = affichage[i][15];
                    affichage[i][15] = affichage[i][16];
                    affichage[i][16] = affichage[i][17];
                    affichage[i][17] = affichage[i][18];
                    affichage[i][18] = affichage[i][19];

                }
            }
            /*
            printf("%c %c ", affichage[0][14-0], affichage[0][14-0+1]);
            affichage[0][14 - 0 - 1] = affichage[0][14 - 0];
            printf("%c %c ", affichage[0][14-0-1], affichage[0][14-0]);
            */

        }
}

