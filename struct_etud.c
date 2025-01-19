#include "struct_etud.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*creer_etu(int type,int ligne,int tour,Liste* l ) créer des Etudiants et les chaines entre eux en fonctions de leurs lignes
  et en les insérents dans le tableau de Liste l. Cette fonction est utilisé dans la fonction placer(FILE* nom_fichier)*/
void creer_etu(int type,int ligne,int tour,Liste* l ){
    Etudiant* e=malloc(sizeof(Etudiant));
    if(e==NULL){
        printf("erreur d'allocation");
        exit(1); //j'arrete tout le programme
    }
    e->type=type;
    type_Etudiant(type,e);
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
        e->position=(-1);

}
/* la fonction type_Etudiant(int type,Etudiant* e) permet d'initialiser les attributs degats, pointsDeVie
   et vitesse en fonction de l'attribut type d'Etudiants. */
void type_Etudiant(int type,Etudiant* e){
    switch(type){
        case 'Z':
            e->degats=1;
            e->pointsDeVie=5;
            e->vitesse=1;
            break;
        case 'M':
            e->degats=3;
            e->pointsDeVie=10;
            e->vitesse=1;
            break;
        case 'L':
            e->degats=5;
            e->pointsDeVie=5;
            e->vitesse=2;
            break;
        case 'S':
            e->degats=1;
            e->pointsDeVie=3;
            e->vitesse=4;
            break;
        case 'X':
            srand(time(NULL));
            e->degats=rand()%4+1;
            e->pointsDeVie=rand()%7+1;
            e->vitesse=rand()%3+1;
            break;
        default:
            printf("type n'existe pas");
            exit(1);
    }
}
/* la fonction placer(FILE* nom_fichier) créer un tableau de Liste d' Etudiant de taille égale au nombre
    de ligne en lisant le fichier contenant les informations par rapport aux vagues. Elle utilise creer_etu(int type,int ligne,int tour,Liste* l )
    pour ajouter ces Etudiants.   */
Liste* placer(FILE * nom_fichier){

Liste*l=malloc(NOMBRE_LIGNES*sizeof(Liste));
if(l==NULL){
    printf("erreur d'allocation");
    exit(1); //j'arrete tout le programme
}
for(int i=0;i<7;i++){
l[i].fin=NULL;
l[i].tete=NULL;
l[i].prochain=NULL;
}

int tour,ligne;
char type;
int header;
fscanf(nom_fichier, "%d", &header);
while (fscanf(nom_fichier, "%d %d %c", &tour, &ligne, &type) == 3) {
    printf("%d ",type );
    creer_etu(type,ligne,tour,l);
    }
    printf("\n");

return l;
}
/* liberer_liste(liste *l) permet de liberer la memoire allouée lors de l'appel de la fonction placer. */
void liberer_liste(Liste *l){
    for (int i=0;i<NOMBRE_LIGNES;i++){
        Etudiant *courant=l[i].tete;
        while(courant!=l[i].fin){
            Etudiant* temp=courant;
            courant=courant->next;
            free(temp);
        }
        free(courant);
    }
    free(l);
    
}

