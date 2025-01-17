#include "struct_etud.h"
#include <stdio.h>
#include <stdlib.h>




void creer_etu(int type,int ligne,int tour,Liste* l ){
    Etudiant* e=malloc(sizeof(Etudiant));
    if(e==NULL){
        printf("erreur d'allocation");
        exit(1); //j'arrete tout le programme
    }
    e->type=type;
    //type_mechant(type) , fonction qui va attribuer les pv et vitesse en fonction du monstre, pour l'instant on met juste 5 pv et 1 vitesse
    e->pointsDeVie=5;
    e->vitesse=1;
    e->next=NULL;
    e->next_line=NULL;
    if(tour==1||l[ligne-1].tete==NULL){
        e->prev_line=NULL;
        l[ligne-1].fin=e;
        l[ligne-1].tete=e;
        l[ligne-1].prochain=e;
    }
    else{
        e->prev_line=l[ligne-1].fin;
        l[ligne-1].fin->next_line=e;
        l[ligne-1].fin->next=e;
        l[ligne-1].fin=e;
        }
        e->ligne=ligne;
        e->tour=tour;
        e->position=-1;
   
}