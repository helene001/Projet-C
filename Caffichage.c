#include <stdio.h>
#include <stdlib.h>
#include "Caffichage.h"
#include "struct_etud.h"
#include "struct_jeu.h"
#include <unistd.h>
#include <string.h>
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


/* affichejeu(Jeu *jeu) affiche les Etudiants avec leurs PV tour par tour, tant qu'ils ne sont pas tous mort ou que le joueur n'a pas perdu*/
void affichejeu(Jeu *jeu){
    Etudiant* tab[NOMBRE_LIGNES][15];
    while(jeu->etudiants!=NULL){
        memset(tab,0,sizeof(tab));//intitialise tout les éléments de tab à NULL
        Etudiant *courant=jeu->etudiants;
        while(courant!=jeu->dernier){
            if(courant->position<15 && courant->tour<=jeu->tour){
                tab[(courant->ligne)-1][courant->position]=courant;
                courant=courant->next;
            }else{
                courant=courant->next;
            }
            if(jeu->dernier->position<15 && jeu->dernier->tour<=jeu->tour){
                tab[(jeu->dernier->ligne)-1][jeu->dernier->position]=jeu->dernier;
            }
        }
        for (int i = 0; i < NOMBRE_LIGNES; i++){
            printf("%d|",i+1);
            for (int j = 0; j < 15; j++){
                if(tab[i][j]!=NULL){
                        printf("%3d%c ",tab[i][j]->pointsDeVie,tab[i][j]->type);
                }else{
                    printf("%4c ", '.');
                }
            }
            printf("\n");
        }
        jeu->tour+=1;
        Etudiant *courant1=jeu->etudiants;
        while(courant1!=jeu->dernier){
            if( courant1->tour<=jeu->tour){
                avancer(courant1);
                if(courant1->position<=0){
                    perdu(jeu);
                    exit(1);
                }
                courant1=courant1->next;
            }else{
                courant1=courant1->next;
            }
            if( jeu->dernier->tour<=jeu->tour){
                avancer(jeu->dernier);
            }
        }
        printf("\n");
        printf("\n");
        usleep(500000);
        
    }
    gagner();

}

//a faire mieux apres perdu et gagner

/* perdu() s'occupe de l'affichage en cas de victoire*/
void perdu(Jeu* jeu){
    //system("clear");
    printf("vous avez perdu gros Neuille\n");
    liberer_etudiant(jeu);
    free(jeu);
}
/* perdu() s'occupe de l'affichage en cas de victoire*/
void gagner(){
    system("clear");
    printf("vous avez gagner");
}

//fonction qui verifie si le fichier est conforme
int fichierConforme(FILE* fichierVague)
{
    //gagnotte conforme ?
    char chaineCagnotte[100] = "";
    int i = 0;
    fgets(chaineCagnotte, 100, fichierVague);

    while ((chaineCagnotte[i] != '\0') && (chaineCagnotte[i] != '\n'))
    {

        if ((chaineCagnotte[i] < 48) || (chaineCagnotte[i] > 57))
        {
            printf("Cagnotte non conforme\n"); //les valeurs ascii des chiffres de 0 à 9 sont entre 48 et 57 inclus
            return 0; //0 signifie faux donc ici fichier NON conforme
        }
        i++;
    }
    
    //positions conformes ?
    char chainePositions[100] = "";
    while (fgets(chainePositions, 100, fichierVague) != NULL)
    {
        if (strlen(chainePositions) > 6)
        {
            printf("Format des lignes non conforme.\n");
            return 0;
        }
        else if ((chainePositions[0] < 49) || (chainePositions[0] > 57) || (chainePositions[2] < 49) || (chainePositions[2] > 57))
        {
            printf("Positions non conformes.\n");
            return 0;
        }
        else if ((chainePositions[1] != ' ') || (chainePositions[3] != ' '))
        {
            printf("Espaces entre les positions non conformes.\n");
            return 0;
        }
        else if ((chainePositions[4] != 'Z') && (chainePositions[4] != 'M') && (chainePositions[4] != 'L') && (chainePositions[4] != 'S') && (chainePositions[4] != 'X'))
        {
            printf("Type non conforme.\n");
            return 0;
        }
    }
    printf("Fichier conforme.\n");
    rewind(fichierVague); //si tout va bien, remettre le curseur au debut du fichier
    return 1;
}
