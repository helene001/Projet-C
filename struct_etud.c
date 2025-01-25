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
        liberer_liste(l);
        //fclose(fichier vague)
        exit(1); //j'arrete tout le programme
    }
    e->type=type;
    type_Etudiant(type,e,l);
    e->next=NULL;
    e->next_line=NULL;
    if(l[ligne-1].tete==NULL){ //si e est le premier sur sa ligne 
        e->prev_line=NULL;
        l[ligne-1].fin=e;
        l[ligne-1].tete=e;
        l[ligne-1].prochain=e;
    }
    else{// sinon on chaine e avec l'Etudiant qui est devant lui (qui est le dernier avant l'ajout de e)
        e->prev_line=l[ligne-1].fin;
        l[ligne-1].fin->next_line=e;
        l[ligne-1].fin->next=e;
        l[ligne-1].fin=e;
        }
        e->ligne=ligne;
        e->tour=tour;
        e->position=15;

}
/* la fonction type_Etudiant(int type,Etudiant* e) permet d'initialiser les attributs degats, pointsDeVie
   et vitesse en fonction de l'attribut type d'Etudiants. */
void type_Etudiant(int type,Etudiant* e,Liste *l){
    switch(type){
        case 'Z':
            e->degats=1;
            e->pointsDeVie=5;
            e->vitesse=1;
            break;
        case 'M':
            e->degats=3;
            e->pointsDeVie=9;
            e->vitesse=1;
            e->avancer_ou_non=1;
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
            e->degats=rand()%4+1;
            e->pointsDeVie=rand()%7+1;
            e->vitesse=rand()%3+1;
            break;
        default:
            printf("type n'existe pas");
            free(e);
            liberer_liste(l);
            //fclose(fichier_vague) apres
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
    fclose(nom_fichier);
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
srand(time(NULL));//j'intialise le generateur aleatoire pour le type 'X'
fscanf(nom_fichier, "%d", &header);
while (fscanf(nom_fichier, "%d %d %c", &tour, &ligne, &type) == 3) { /* tant que l'on a 3 colonnes de la forme tour d'apparition ligne type on 
                                                                        lit les élèments du fichier, on les mets dans les variables tour,ligne,char et on
                                                                        les utilise pour créer un nouvel Etudiant */
    creer_etu(type,ligne,tour,l);
    }
    printf("\n");
//fclose(fichierMechant);
return l;
}
/* liberer_liste(liste *l) permet de liberer la memoire allouée lors de l'appel de la fonction placer. */
void liberer_liste(Liste *l){
    for (int i=0;i<NOMBRE_LIGNES;i++){
        Etudiant *courant=l[i].tete;
        while(courant!=l[i].fin){//tant que l'on a pas le dernier Etudiant sur la ligne en passant au prochain Etudiants et en liberant la mémoire de l'étudiant courant.
            Etudiant* temp=courant;
            courant=courant->next;
            free(temp);
        }
        free(courant);
    }
    free(l);
    
}
/* touche_Etudiant(Etudiant *e, int degat_tourelle,int ligne ,Liste *l) permet de de prendre en compte
    les dégats des tourelles et, dans le cas ou l'Etudiant n'a plus de Points de vie, de le tuer. */
void touche_Etudiant(Etudiant *e, int degat_tourelle,int ligne ,Liste *l){
    e->pointsDeVie-=degat_tourelle;
    if (e->pointsDeVie<=0){ //si l'Etudiant meurt, on l'enlève de la liste et on libere sa mémoire
        if (l[ligne-1].tete==e){
            e->next->prev_line=NULL;
            l[ligne-1].tete=e->next;
            e->next=NULL;
            e->next_line=NULL;
            free(e);
        }else if(l[ligne-1].fin==e){
            l[ligne-1].fin=NULL;
            l[ligne-1].tete=NULL;
            l[ligne-1].prochain=NULL;
            free(e);
        }else{
            e->prev_line->next=e->next;
            e->prev_line->next_line=e->next_line;
            e->next->prev_line=e->prev_line;
            e->next_line->prev_line=e->prev_line;
            e->next=NULL;
            e->next_line=NULL;
            e->prev_line=NULL;
            free(e);
        }
    }
}
/* avancer(Etudiant* e,Liste *l) fait avancer les Etudiants en fonction de leur vitesse et de la position
    de l'Etudiant qui le précède.*/

void avancer(Etudiant* e,Liste *l){
    //si e est le premier de sa ligne, on a pas de problèmes.
    if (e->prev_line==NULL){
        if(e->type=='M'){
            if(e->avancer_ou_non){
                    e->position-=1;
                    e->avancer_ou_non=0; /* e n'avancera pas au prochain affichage*/
                }else{
                    e->avancer_ou_non=1;
                }
        }else{
            e->position-=e->vitesse;
        }
        
    }else{
    switch (e->type){
        case 'S':
            if (e->position-3>e->prev_line->position){ /* je vérifie si il n'y a pas un autre etudiant qui peut gêner e*/
                e->position-=3;
            }else if(e->position-2>e->prev_line->position){
                e->position-=2;
            }else if(e->position-1>e->prev_line->position){
                e->position-=1;
            }
            break;
        case 'X':
            int vit=e->vitesse; /* vu que la vitesse de X peut varier, je suis obligé de faire une boucle*/
            while(vit>0){
                if(e->position-vit>e->prev_line->position){
                    e->position-=vit;
                    break;
                }else{
                    vit-=1;
                }
            }
            break;
        case 'M':
            if (e->position-1>e->prev_line->position){
                if(e->avancer_ou_non){
                    e->position-=1;
                    e->avancer_ou_non=0; /* e n'avancera pas au prochain affichage*/
                }else{
                    e->avancer_ou_non=1;
                }
            }else{
                e->avancer_ou_non=1;
            }
            break;
        default :
            if (e->position-1>e->prev_line->position){
                e->position-=1;
            }
            break;
    }
    }
}















