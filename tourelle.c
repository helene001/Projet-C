#include "Tourelle.h"

Tourelle *creerTourelle(int ligne, int position, int type)
{
    Tourelle *nouvelleTourelle = malloc(sizeof(Tourelle));
    if (!nouvelleTourelle)
    {
        printf("Allocation mémoire pour la tourelle échouée");
        exit(EXIT_FAILURE);
    }

    nouvelleTourelle->ligne = ligne;
    nouvelleTourelle->position = position;
    nouvelleTourelle->type = type;

    switch (type)
    {
    case TOURRELE_DE_BASE:
        nouvelleTourelle->prix = PRIX_TOURRELE_DE_BASE;
        nouvelleTourelle->pointsDeVie = POINTS_DE_VIE_TOURRELE_DE_BASE;
        break;
    case TOURRELE_RALENTISSEUR:
        nouvelleTourelle->prix = PRIX_TOURRELE_RALENTISSEUR;
        nouvelleTourelle->pointsDeVie = POINTS_DE_VIE_TOURRELE_RALENTISSEUR;
        break;
    case TOURRELE_MINE:
        nouvelleTourelle->prix = PRIX_TOURRELE_MINE;
        nouvelleTourelle->pointsDeVie = POINTS_DE_VIE_TOURRELE_MINE;
        break;
    case TOURRELE_ZONE:
        nouvelleTourelle->prix = PRIX_TOURRELE_ZONE;
        nouvelleTourelle->pointsDeVie = POINTS_DE_VIE_TOURRELE_ZONE;
        break;
    case TOURRELE_MUR:
        nouvelleTourelle->prix = PRIX_TOURRELE_MUR;
        nouvelleTourelle->pointsDeVie = POINTS_DE_VIE_TOURRELE_MUR;
        break;
    }

    nouvelleTourelle->next = NULL;
    return nouvelleTourelle;
}


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

 void attaquerLigne(Jeu *jeu, Tourelle *tourelle)
{
    Etudiant *ennemi = jeu->etudiants;

    // Parcourir les vilains sur la ligne de la tourelle
    while (ennemi != NULL)
    {
        if (ennemi->ligne == tourelle->ligne)
        {
            ennemi->pointsDeVie -= 10; // Exemple : inflige 10 points de dégâts
            if (ennemi->pointsDeVie <= 0)
            {
                printf(COULEUR_VERT "Un ennemi a été éliminé sur la ligne %d !\n" COULEUR_REINITIALISER, tourelle->ligne);
                // Supprimer l'ennemi de la liste
                // Implémentation à ajouter
            }
            break; // La tourelle de base attaque un seul ennemi à la fois
        }
        ennemi = ennemi->next;
    }
}

 void ralentirEnnemi(Jeu *jeu, Tourelle *tourelle)
{
    Etudiant *ennemi = jeu->etudiants;

    // Parcourir les vilains sur la ligne de la tourelle
    while (ennemi != NULL)
    {
        if (ennemi->ligne == tourelle->ligne)
        {
            ennemi->vitesse = (ennemi->vitesse > 1) ? ennemi->vitesse - 1 : 1; // Réduire la vitesse sans tomber en dessous de 1
            printf(COULEUR_VERT "Un ennemi sur la ligne %d a été ralenti (vitesse actuelle : %d).\n" COULEUR_REINITIALISER, tourelle->ligne, ennemi->vitesse);
            break; // La tourelle ralentisseur affecte un seul ennemi à la fois
        }
        ennemi = ennemi->next;
    }
}

 void attaquerZone(Jeu *jeu, Tourelle *tourelle)
{
    Etudiant *ennemi = jeu->etudiants;

    // Parcourir tous les vilains dans un rayon de 2 positions autour de la tourelle
    while (ennemi != NULL)
    {
        if (ennemi->ligne == tourelle->ligne &&
            abs(ennemi->position - tourelle->position) <= 2) // Rayon de 2 positions
        {
            ennemi->pointsDeVie -= 5; // Exemple : inflige 5 points de dégâts
            if (ennemi->pointsDeVie <= 0)
            {
                printf(COULEUR_VERT "Un ennemi a été éliminé sur la ligne %d à la position %d !\n" COULEUR_REINITIALISER,
                       tourelle->ligne, ennemi->position);
                // Supprimer l'ennemi de la liste
                // Implémentation à ajouter
            }
        }
        ennemi = ennemi->next;
    }
}

void actionsTourelles(Jeu *jeu)
{
    Tourelle *tourelle = jeu->tourelles;

    while (tourelle != NULL)
    {
        switch (tourelle->type)
        {
        case TOURRELE_DE_BASE:
            attaquerLigne(jeu, tourelle);
            break;
        case TOURRELE_RALENTISSEUR:
            ralentirEnnemi(jeu, tourelle);
            break;
        case TOURRELE_ZONE:
            attaquerZone(jeu, tourelle);
            break;
        case TOURRELE_MUR:
            // Les murs n'ont pas d'action offensive
            break;
        default:
            printf("Tourelle inconnue...");
        }
        tourelle = tourelle->next;
    }
}
