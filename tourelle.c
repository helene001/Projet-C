#include "Tourelle.h"
#include "struct_jeu.h"
#include "struct_etud.h"
#include <string.h>
Tourelle *creerTourelle(int ligne, int position, int choix_joueur,Jeu *jeu){

    Tourelle *nouvelleTourelle = malloc(sizeof(Tourelle));
    if (!nouvelleTourelle)
    {
        printf("Allocation mémoire pour la tourelle échouée");
        exit(EXIT_FAILURE);
    }

    nouvelleTourelle->ligne = ligne;
    nouvelleTourelle->position = position;
    nouvelleTourelle->next=NULL;
    switch (choix_joueur)
    {
    case 1: //tourelle_de_base:
        nouvelleTourelle->prix = 100;
        nouvelleTourelle->pointsDeVie = 5;
        nouvelleTourelle->type='T';
        nouvelleTourelle->degats=2;
        break;
    case 2: //tourelle_ralentisseuse:
        nouvelleTourelle->prix = 150;
        nouvelleTourelle->pointsDeVie = 5;
        nouvelleTourelle->type='{';
        nouvelleTourelle->degats=1;
        break;
    case 3: //tourelle_mine:
        nouvelleTourelle->prix = 100;
        nouvelleTourelle->pointsDeVie = 1;
        nouvelleTourelle->type='*';
        nouvelleTourelle->degats=5;
        break;
    case 4: //tourelle_zone:
        nouvelleTourelle->prix = 200;
        nouvelleTourelle->pointsDeVie = 7;
        nouvelleTourelle->type='<';
        nouvelleTourelle->degats=2;
        break;
    case 5: //tourelle_mur:
        nouvelleTourelle->prix = 50;
        nouvelleTourelle->pointsDeVie = 10;
        nouvelleTourelle->type='|';
        nouvelleTourelle->degats=0;
        break;
    }
    return nouvelleTourelle;
}
/* chainage_tourelle(Jeu * jeu) demande a l'utilisateur de choisir les tourelles qu'il veut acheter et les places dans une liste chainée dans jeu*/
void chainage_tourelle(Jeu * jeu){
    jeu->tourelles=NULL;
    int fini=0;
    Tourelle * tab[NOMBRE_LIGNES][15];
    memset(tab,0,sizeof(tab));
    while (jeu->cagnotte>50 && !fini){//tant que le joueur a de l'argent ou qu'il décide s'arreter, on ajoute des tourelles
        int i;//dans i va etre stocker le type de tourelle
        int ligne;
        int position;
        printf("il vous reste %d crédits\n\n",jeu->cagnotte);
        printf("Quelle type de tourelle voulez vous?\n\n");
        printf("tapez 1 pour placer une tourelle de base. PRIX 100\n\n");
        printf("tapez 2 pour placer une tourelle ralentisseuse. PRIX 150\n\n");
        printf("tapez 3 pour placer une mine. PRIX 100\n\n");
        printf("tapez 4 pour placer une tourelle avec degat de zone. PRIX 200\n\n");
        printf("tapez 5 pour placer un mur. PRIX 50\n\n");
        scanf("%d" ,&i);

        while(i!=1 && i!=2 && i!=3 && i!=4 && i!=5 ){//tant que i n'est pas un type qui existe, on redemande à l'utilisateur d'écrire le type qu'il veut
            printf("Ce type de tourelle n'existe pas veuillez chosir correctement\n\n");
            printf("il vous reste %d crédits\n\n",jeu->cagnotte);
            printf("Quelle type de tourelle voulez vous?\n");
            printf("tapez 1 pour placer une tourelle de base. PRIX 100\n\n");
            printf("tapez 2 pour placer une tourelle ralentisseuse. PRIX 150\n\n");
            printf("tapez 3 pour placer une mine. PRIX 100\n\n");
            printf("tapez 4 pour placer une tourelle avec degat de zone. PRIX 200\n\n");
            printf("tapez 5 pour placer un mur. PRIX 50\n\n");
            scanf("%d" ,&i);
        }
        int pas_assez=1;//pas_assez=1 signifie qu'on manque de crédit pour acheter une certaine défense
        while((pas_assez)){
            pas_assez=0;//on l'initialise a 0
            //le switch verifie que l'argent restant n'est pas inférieur au prix de la tourelle de type i. Si c'est le cas, pas_assez=1
            switch(i){
                case 1:
                    if (jeu->cagnotte<100){
                        pas_assez=1;
                    }
                    break;
                case 2:
                    if (jeu->cagnotte<150){
                        pas_assez=1;
                    }
                    break;
                case 3:
                    if (jeu->cagnotte<100){
                        pas_assez=1;
                    }
                    break;
                case 4:
                    if (jeu->cagnotte<200){
                        pas_assez=1;
                    }
                    break;
                case 5:
                    if (jeu->cagnotte<50){
                        pas_assez=1;
                    }
                    break;
            }
            if (pas_assez){//si on a pas assez on redemande au joueur et on reboucle
                printf("Vous n'avez pas assez\n\n");
                printf("il vous reste %d crédits\n\n",jeu->cagnotte);
                printf("Quelle type de tourelle voulez vous?\n\n");
                printf("tapez 1 pour placer une tourelle de base. PRIX 100\n\n");
                printf("tapez 2 pour placer une tourelle ralentisseuse. PRIX 150\n\n");
                printf("tapez 3 pour placer une mine. PRIX 100\n\n");
                printf("tapez 4 pour placer une tourelle avec degat de zone. PRIX 200\n\n");
                printf("tapez 5 pour placer un mur. PRIX 50\n\n");
                scanf("%d" ,&i);
            }
        }
            
        printf("choisissez une ligne entre 1 et 7\n");
        scanf("%d" ,&ligne);
        printf("choisissez une position entre 0 et 13\n");
        scanf("%d" ,&position);
        int position_occupe=0;
        if (jeu->tourelles!=NULL){
            if(jeu->tourelles==jeu->derniere){
                if(jeu->tourelles->ligne==ligne && jeu->tourelles->position==position){
                    position_occupe=1;
                }
            }else{
                Tourelle * courant=jeu->tourelles;
                while(courant!=jeu->derniere){//on parcourt la liste chainée de tourelles
                    if((courant->ligne==ligne) && (courant->position==position)){
                        position_occupe=1;//si on trouve une tourelle à la ligne et à la position choisi, on m.a.j position_occupe
                    }
                    courant=courant->next;
                }
            }
        }
        while(ligne < 1 || ligne > 7 || position < 0 || position > 13 || position_occupe){//on boucle tant que notre tourelle n'est pas placée correctement
            position_occupe=0;
            printf("position invalide\n\n");
            printf("choisissez une ligne entre 1 et 7\n\n");
            scanf("%d" ,&ligne);
            printf("choisissez une position entre 0 et 13\n\n");
            scanf("%d" ,&position);
            if (jeu->tourelles!=NULL){
                if(jeu->tourelles==jeu->derniere){
                    if(jeu->tourelles->ligne==ligne && jeu->tourelles->position==position){
                        position_occupe=1;
                    }
                }else{
                    Tourelle * courant=jeu->tourelles;
                    while(courant!=jeu->derniere){
                        if(courant->ligne==ligne && courant->position==position){
                            position_occupe=1;
                        }
                        courant=courant->next;
                    }
                }
            }
        }
        //Si on a surmonté tout les problèmes possibles précedent, on ajoute la nouvelle tourelle aux autre tourelles
        Tourelle* t=creerTourelle(ligne,position,i,jeu);
        if(jeu->tourelles==NULL){//si c'est la première
            jeu->tourelles=t;
            jeu->derniere=t;
            jeu->tourelles->next=jeu->derniere;
            
        }else{
        jeu->derniere->next=t;
        jeu->derniere=t;
        }
        jeu->cagnotte-=t->prix;//on enlève le prix de notre tourelle à la cagnotte
        tab[t->ligne-1][t->position]=t;//on place notre tourelle dans un tableau temporaire.
        for (int i = 0; i < NOMBRE_LIGNES; i++){/*on affiche la tourelle en utilisant le même principe que dans afficher_jeu de Caffichage*/
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
        char choix[10];
        printf("Voulez vous vous arréter (OUI si vous voulez sinon tapez n'importe quoi)\n");
        scanf("%9s", choix);
        if (strcmp(choix,"OUI")==0){//si le joueur ecrit OUI, il a fini de placer les tourelles sinon on continue.
            break;
        }
    }
}

Tourelle *trouver_pos_exacte_tour(Jeu* jeu,int ligne ,int pos){
    Tourelle* courante=jeu->tourelles;
    while(courante!=NULL){
        if(courante->ligne==ligne && courante->position==pos){
            return courante;
        }
        courante=courante->next;
    }
    return NULL;
}

void toucher_Tourelle(Jeu *jeu,Tourelle* tourelle,int degat){
    if(tourelle==NULL){
        return;
    }
    tourelle->pointsDeVie-=degat;
    if(tourelle->pointsDeVie<0){
        if(tourelle->type=='*'){
            Etudiant *e=trouver_pos_exacte_etu(jeu,tourelle->ligne,tourelle->position+1);
            if(e){
                touche_Etudiant(e ,tourelle->degats,e->ligne,jeu);
                if(e){//si e est encore vivant
                    e->position-=1;
                }
            }
        }
        Tourelle * courante=jeu->tourelles;
        while(courante->next!=tourelle){
            courante=courante->next;
        }
        courante->next=tourelle->next;
        if (tourelle==jeu->derniere){
            courante=jeu->derniere;
        }
    }
}
/*
void contactTourelles(Jeu *jeu)
{
    Tourelle *tourelle = jeu->tourelles;
    while (tourelle != NULL)
    {
        Etudiant *etudiant = jeu->etudiants;

        while (etudiant != NULL)
        {
            // Vérifie si l'ennemi est au contact avec la tourelle
            if (etudiant->ligne == tourelle->ligne && etudiant->position == tourelle->position)
            {
                printf("Un ennemi de type %d est au contact d'une tourelle !", etudiant->type);

                // Inflige des dégâts ou applique des effets en fonction du type de tourelles

                // Si l'ennemi est détruit
                if (etudiant->pointsDeVie <= 0)
                {
                    printf("Un ennemi a été éliminé !");
                    supprimerVilain(jeu, etudiant);
                }
            }
            etudiant = etudiant->next;
        }
        tourelle = tourelle->next;
    }
}
*/

 void attaquerT(Jeu *jeu, Tourelle *tourelle){
    Etudiant *e=trouver_ligne_etu(jeu,tourelle->ligne);
    if (e!=NULL && e->position<15){
    touche_Etudiant(e,tourelle->degats,tourelle->ligne,jeu);
    }
}

 void ralentirEnnemi(Jeu *jeu, Tourelle *tourelle){
    Etudiant *e=trouver_ligne_etu(jeu,tourelle->ligne);
    if (e!=NULL){//si on a un étudiant sur cette ligne
        while(e!=NULL&&e->position<15){//on touche et ralenti tous les étudiants sur la ligne
        //e->next_line;
        e->vitesse = (e->vitesse > 1) ? e->vitesse - 1 : 1; // Réduit la vitesse sans tomber en dessous de 1
        touche_Etudiant(e,tourelle->degats,tourelle->ligne,jeu);
        e->next_line;
        //Etudiant* e=temp;
        }
        if(e->position<15){
            touche_Etudiant(e,tourelle->degats,tourelle->ligne,jeu);//on fait le cas du dernier sur sa ligne;
        }
    }
            
}

void attaquerZone(Jeu *jeu, Tourelle *tourelle){
    Etudiant *e=trouver_ligne_etu(jeu,tourelle->ligne);
    if(e==NULL){
        return;
    }
    if(e->position>=15){
        return;
    }
    if(tourelle->ligne==1){
        Etudiant * e1=trouver_pos_exacte_etu(jeu,tourelle->ligne+1,e->position);//on cherche l'étudiant juste en dessous de e
        if(e1&&e1->position<15){
            touche_Etudiant(e1,tourelle->degats,tourelle->ligne,jeu);
        }
        if(e->position>0){//on vérifie qu'il peut y a voir quelq'un avant e
        Etudiant * e2=trouver_pos_exacte_etu(jeu,tourelle->ligne,e->position-1);
        if(e2&&e2->position<15){
            touche_Etudiant(e2,tourelle->degats,tourelle->ligne,jeu);
        }
        }
        if(e->position<13){//on vérifie qu'il peut y a voir quelq'un après e
        Etudiant * e3=trouver_pos_exacte_etu(jeu,tourelle->ligne+1,e->position+1);
        if(e3&&e3->position<15){
            touche_Etudiant(e3,tourelle->degats,tourelle->ligne,jeu);
        }
        }
        touche_Etudiant(e1,tourelle->degats,tourelle->ligne,jeu);
    }
    else if(tourelle->ligne==7){
        Etudiant * e1=trouver_pos_exacte_etu(jeu,tourelle->ligne-1,e->position);//on cherche l'étudiant juste en dessous de e
        if(e1&&e1->position<15){
            touche_Etudiant(e1,tourelle->degats,tourelle->ligne,jeu);
        }
        if(e->position>0){//on vérifie qu'il peut y a voir quelq'un avant e
        Etudiant * e2=trouver_pos_exacte_etu(jeu,tourelle->ligne,e->position-1);
        if(e2&&e2->position<15){
            touche_Etudiant(e2,tourelle->degats,tourelle->ligne,jeu);
        }
        }
        if(e->position<13){//on vérifie qu'il peut y a voir quelq'un après e
        Etudiant * e3=trouver_pos_exacte_etu(jeu,tourelle->ligne,e->position+1);
        if(e3&&e3->position<15){
            touche_Etudiant(e3,tourelle->degats,tourelle->ligne,jeu);
        }
        }
        
        touche_Etudiant(e,tourelle->degats,tourelle->ligne,jeu);
    }else{
        Etudiant * e1=trouver_pos_exacte_etu(jeu,tourelle->ligne-1,e->position);//on cherche l'étudiant juste en dessous de e
        if(e1&&e1->position<15){
            touche_Etudiant(e1,tourelle->degats,tourelle->ligne,jeu);
        }
        if(e->position>0){//on vérifie qu'il peut y a voir quelq'un avant e
        Etudiant * e2=trouver_pos_exacte_etu(jeu,tourelle->ligne,e->position-1);
        if(e2&&e2->position<15){
            touche_Etudiant(e2,tourelle->degats,tourelle->ligne,jeu);
        }
        }
        if(e->position<13){//on vérifie qu'il peut y a voir quelq'un après e
        Etudiant * e3=trouver_pos_exacte_etu(jeu,tourelle->ligne,e->position+1);
        if(e3&&e3->position<15){
            touche_Etudiant(e3,tourelle->degats,tourelle->ligne,jeu);
        }
        }
        Etudiant * e4=trouver_pos_exacte_etu(jeu,tourelle->ligne+1,e->position);//on cherche l'étudiant juste au dessus de e
        touche_Etudiant(e4,tourelle->degats,tourelle->ligne,jeu);
        
        touche_Etudiant(e,tourelle->degats,tourelle->ligne,jeu);
    }
    
}

void actionsTourelles(Jeu *jeu)
{
    Tourelle *tourelle = jeu->tourelles;
    while (tourelle != NULL)
    {
        switch (tourelle->type)
        {
        case 'T':
            attaquerT(jeu, tourelle);
            break;
        case '{':
            ralentirEnnemi(jeu, tourelle);
            break;
        case '<':
            attaquerZone(jeu, tourelle);
            break;
        default:
            break;
        }
        tourelle = tourelle->next;
    }
}

void liberer_tourelle(Jeu* j){
        Tourelle *courant=j->tourelles;
        while(courant!=j->derniere){
        Tourelle* temp=courant;
        courant=courant->next;
        free(temp);
        }
        free(courant);
    }
