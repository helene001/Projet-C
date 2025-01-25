#include <stdio.h>
#include <stdlib.h>
#include "Caffichage.h"
#include "struct_etud.h"
#include <time.h>
#define TAILLE_MAX 100
//#define Fichier_vague ... a faire quand on aura plusieurs mode de jeu pour bonne gestion memoire en cas d 'erreur
int main(int argc, char* argv[])
{
    FILE* fichierVague = NULL;
    fichierVague = fopen("ex_vague.txt", "r");
    
    char cagnotte[TAILLE_MAX]= "";
 
    if (fichierVague != NULL)
    {
        //gestion cagnotte
        fgets(cagnotte, TAILLE_MAX, fichierVague);
        printf("Credit restant : %s\n", cagnotte);
        //afficher les vagues AVANT le debut du jeu
        afficheVagues(fichierVague);
        rewind(fichierVague);
        Liste *l=placer(fichierVague);
        fclose(fichierVague);
        affichejeu(l);
        liberer_liste(l);
    }
    else
    {
        printf("Erreur");
    }
    return 0;
}
