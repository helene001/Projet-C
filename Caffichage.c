#include <stdio.h>
#include <stdlib.h>
#include "Caffichage.h"
#include "struct_etud.h"
#include <unistd.h>

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
    char affichage[NOMBRE_LIGNES][NOMBRE_TOURS]; //7 lignes et 9 colonnes
    for (int i = 0; i < NOMBRE_LIGNES; i++)
    {
        for (int j = 0; j < NOMBRE_TOURS; j++)
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
    for (int i = 0; i < NOMBRE_LIGNES; i++)
    {
        printf("%d|", i+1);
        for (int j = 0; j < NOMBRE_TOURS; j++)
            printf("%c\t", affichage[i][j]);
        printf("\n");
    }

}


/* affichejeu(Liste *l) affiche les Etudiants avec leurs PV tour par tour tant qu'ils ne sont pas tous mort ou que le joueur n'a pas perdu*/
void affichejeu(Liste *l){
    
    int tour_courant=0;
    while(l[0].tete!=NULL || l[1].tete!=NULL || l[2].tete!=NULL || l[3].tete!=NULL || l[4].tete!=NULL || l[5].tete!=NULL || l[6].tete!=NULL){

        for (int i = 0; i < NOMBRE_LIGNES; i++){
            Etudiant *courant=l[i].tete;
            if(courant!=NULL){// on vérifie si la ligne a des Etudiants ou pas
                if (l[i].prochain!=NULL){
                    if (l[i].prochain->tour<=tour_courant){ 
                            l[i].prochain=l[i].prochain->next;
                        }
                }
                while(courant!=l[i].prochain){
                    avancer(courant,l);
                    if(courant->position<=0){
                        perdu(l);
                        return;
                    }
                    courant=courant->next_line;
                }
                courant =l[i].tete;
            }
            printf("%d|", i + 1);
            for (int j = 0; j < 15; j++){

                if(courant!=NULL){
                    if (courant->position==j){
                        printf("%3d%c ",courant->pointsDeVie,courant->type);
                        courant=courant->next_line;
                    }else{
                        printf("%4c ", '.');
                    }
                }else{
                    printf("%4c ", '.');
                }
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");
        usleep(500000);
        tour_courant+=1;
    }
    gagner();

}

//perdu et  gagner a faire mieux apres

/* perdu() s'occupe de l'affichage en cas de victoire*/
void perdu(){
    system("clear");
    printf("vous avez perdu \n");
}
/* perdu() s'occupe de l'affichage en cas de victoire*/
void gagner(){
    system("clear");
    printf("vous avez gagner");
}


