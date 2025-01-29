#include "struct_etud.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct_jeu.h"
#include <string.h>

/*creer_etu(int type,int ligne,int tour,Jeu* jeu ,FILE* nom_fichier ) créer des Etudiants et les chaines entre eux en fonctions de leurs lignes
  .Cette fonction est utilisé dans la fonction placer(Jeu* jeu,FILE* nom_fichier)*/
Etudiant* creer_etu(int type,int ligne,int tour,Jeu* jeu ,FILE* nom_fichier){
    Etudiant* e=malloc(sizeof(Etudiant));
    if(e==NULL){// si il y'a une erreur d'allocation la mémoire est libéré correctement
        printf("erreur d'allocation");
        liberer_etudiant(jeu);
        free(jeu);
        fclose(nom_fichier);
        exit(1); //j'arrete tout le programme
    }
    e->type=type;
    type_Etudiant(type,e,jeu);//type_Etudiant est appelé pour initialiser les attributs degats, pointsDeVie et vitesse  
    e->next=NULL;
    e->next_line=NULL;
    e->prev_line=NULL;
    e->prev=NULL;
    e->ligne=ligne;
    e->tour=tour;
    e->position=15; 

}
/* la fonction type_Etudiant(int type,Etudiant* e,Jeu* j) permet d'initialiser les attributs degats, pointsDeVie
   et vitesse en fonction de l'attribut type d'Etudiants. */
void type_Etudiant(int type,Etudiant* e,Jeu* j){
    
    switch(type){
        case 'Z':
            e->degats=1;
            e->pointsDeVie=5;
            e->PV_max=5;
            e->vitesse=1;
            break;
        case 'M':
            e->degats=3;
            e->pointsDeVie=9;
            e->PV_max=9;
            e->vitesse=1;
            e->un_sur_2=1;
            break;
        case 'D':
            e->degats=1;
            e->pointsDeVie=3;
            e->PV_max=3;
            e->vitesse=1;
            break;
        case 'S':
            e->degats=1;
            e->pointsDeVie=3;
            e->PV_max=3;
            e->vitesse=4;
            break;
        case 'X':
            e->degats=rand()%4+1;
            e->pointsDeVie=rand()%7+1;
            e->PV_max=e->pointsDeVie;
            e->vitesse=rand()%3+1;
            break;
            /* il n'y a pas besoin de mettre un cas default car les types d'Etudiant sont déja vérifié
            dans la fonction fichierConforme de Caffichage */
    }
}
/* la fonction placer(Jeu* jeu,FILE* nom_fichier) chaine doublement les Etudiant
    dans jeu en lisant le fichier contenant les informations par rapport aux vagues. Elle utilise creer_etu(int type,int ligne,int tour,Jeu* jeu,FILE* nom_fichier )
    pour ajouter ces Etudiants.   */
void placer(Jeu *jeu,FILE* nom_fichier){
int tour,ligne;
char type;
int header;
srand(time(NULL));//j'intialise le generateur aleatoire pour le type 'X'
fscanf(nom_fichier, "%d", &header);//on saute la première ligne ou il y a la cagnotte.
fscanf(nom_fichier, "%d %d %c", &tour, &ligne, &type);
Etudiant* e=creer_etu(type,tour,ligne,jeu,nom_fichier);
jeu->etudiants=e;
jeu->dernier=e;
jeu->etudiants->next=jeu->dernier;
while (fscanf(nom_fichier, "%d %d %c", &tour, &ligne, &type) == 3) {//tant que le fichier est de la forme tour ligne type on boucle
    jeu->dernier->next=creer_etu(type,ligne,tour,jeu,nom_fichier);//on chaine doublement le nouveau étudiants avec l'ancien dernier
    jeu->dernier->next->prev=jeu->dernier;
    jeu->dernier=jeu->dernier->next; 
    }
}
/* connecte_ligne(Jeu* jeu) permet de doublement chainer les étudiants entre eux par rapport à leur ligne*/
void connecte_ligne(Jeu* jeu){
    for (int i=1;i<=NOMBRE_LIGNES;i++){
        Etudiant* courant=jeu->etudiants;
        while(courant!=jeu->dernier && courant->ligne !=i){//on cherche le premier étudiants sur la ligne i
            courant=courant->next;
        }
        if(courant->next==NULL){//il n'y a pas d'étudiants a la ligne i
            continue;
        }else{
            Etudiant* dernier_ligne=courant; // l'etudiant dernier_ligne pointe sur le dernier etudiants trouvé sur la ligne i
            courant=courant->next;
            while(courant!=jeu->dernier){
                if (courant->ligne==dernier_ligne->ligne){
                    dernier_ligne->next_line=courant; //on chaine les deux étudiants sur la même ligne
                    courant->prev_line=dernier_ligne;
                    dernier_ligne=courant; //le nouveau étudiant trouvé sur la ligne i devient dernier_ligne
                    courant=courant->next; //on continue de parcourir la liste chainée
                }else{
                    courant=courant->next;
                }
            }
            if(jeu->dernier->ligne==dernier_ligne->ligne){//on fait le cas du dernier étudiant
                dernier_ligne->next_line=jeu->dernier;
                jeu->dernier->prev_line=dernier_ligne;
            }
        }
    }
}

/* liberer_liste(Jeu *l) permet de liberer la memoire allouée par la liste chainée d'étudiants */
void liberer_etudiant(Jeu* j){
        Etudiant *courant=j->etudiants;
        while(courant!=j->dernier){
        Etudiant* temp=courant;
        courant=courant->next;
        free(temp);
        }
        free(courant);
    }
/* touche_Etudiant(Etudiant *e, int degat_tourelle,int ligne ,Jeu * jeu) permet  de prendre en compte
    les dégats des tourelles et, dans le cas ou l'Etudiant n'a plus de Points de vie, de le tuer. */
void touche_Etudiant(Etudiant *e, int degat_tourelle, int ligne, Jeu *jeu){
    e->pointsDeVie-=degat_tourelle;
    if (e->pointsDeVie<=0) {//si l'étudiant meurt, on l'enlève de la liste chainée
        if (e->prev!=NULL) { //si ce n'est le premier de la chaine
            e->prev->next=e->next;
        }else if (jeu->etudiants==e){ //si c'est le premier de la liste
            jeu->etudiants=e->next; 
        }
        if (e->next!=NULL) {//si ce n'est pas le dernier de la liste
            e->next->prev=e->prev;
        } else if (jeu->dernier==e) {//si c'est le dernier de la liste
            jeu->dernier=e->prev;
        }
        if (e->prev_line!=NULL) {//si ce n'est pas le premier de sa ligne
            e->prev_line->next_line=e->next_line;
        }
        if (e->next_line!=NULL) {//si ce n'est pas le dernier de sa ligne
            e->next_line->prev_line=e->prev_line;
        }
        free(e);
    }
}
/* Cette fonction permet de retrouver facilement le premier étudiant sur sa ligne*/
Etudiant * trouver_ligne(Jeu * jeu,int ligne){
    Etudiant * courant=jeu->etudiants;
    while(courant!=NULL){//
        if (courant->ligne==ligne){
            while(courant->prev_line!=NULL){//si ce n'est pas le premier sur sa ligne, on recule sur la ligne
                courant=courant->prev_line;
            }
            return courant;
        }else{
            courant=courant->next;
        }
    }
    return NULL;
}

/* avancer(Etudiant* e) fait avancer les Etudiants en fonction de leur vitesse et de la position
    de l'Etudiant qui le précède.*/
void avancer(Etudiant* e){
    if (e->prev_line==NULL){
        if(e->type=='M'){
            if(e->un_sur_2){
                    e->position-=1;
                    e->un_sur_2=0; /* e n'avancera pas au prochain affichage*/
                }else{
                    e->un_sur_2=1;
                }
        }else{
            e->position-=e->vitesse;
        }
        //si e est le premier de sa ligne, on a pas de problèmes.
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
                if(e->un_sur_2){
                    e->position-=1;
                    e->un_sur_2=0; /* e n'avancera pas au prochain affichage*/
                }else{
                    e->un_sur_2=1;
                }
            }else{
                e->un_sur_2=1;
            }
            break;
        case 'D' :
            Etudiant *prochain_ligne= e->next_line;
            Etudiant *precede_ligne= e->prev_line;
            /* le docteur soigne toute sa ligne*/
            while(prochain_ligne!=NULL){
                if(prochain_ligne->pointsDeVie<prochain_ligne->PV_max){
                    prochain_ligne->pointsDeVie+=1;
                }
                prochain_ligne=prochain_ligne->next_line;
            }
            while(precede_ligne!=NULL){
                if(precede_ligne->pointsDeVie<precede_ligne->PV_max){
                    precede_ligne->pointsDeVie+=1;
                }
                precede_ligne=precede_ligne->prev_line;
            }
            if (e->position-1>e->prev_line->position){
                e->position-=1;
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

















