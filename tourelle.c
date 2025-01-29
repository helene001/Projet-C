#include "Tourelle.h"

/*
faut que je finisse la foction occupTourelle avec la liste chaînée
int OccupTourelle(int position, int ligne){
    if (OccLigne[ligne]==1 && OccPosition[position]==1) 
        return 0;
    else
        return 1;
}
*/
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
                    liberer_etudiant(jeu);
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

    // Parcourir les étudiants sur la ligne de la tourelle
    while (ennemi != NULL)
    {
        if (ennemi->ligne == tourelle->ligne)
        {
            ennemi->pointsDeVie -= 10; // Exemple : inflige 10 points de dégâts
            if (ennemi->pointsDeVie <= 0)
            {
                printf("Un ennemi a été éliminé sur la ligne %d !\n", tourelle->ligne);
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

    // Parcourir les étudiants sur la ligne de la tourelle
    while (ennemi != NULL)
    {
        if (ennemi->ligne == tourelle->ligne)
        {
            ennemi->vitesse = (ennemi->vitesse > 1) ? ennemi->vitesse - 1 : 1; // Réduire la vitesse sans tomber en dessous de 1
            printf("Un ennemi sur la ligne %d a été ralenti (vitesse actuelle : %d).\n", tourelle->ligne, ennemi->vitesse);
            break; // La tourelle ralentisseur affecte un seul ennemi à la fois
        }
        ennemi = ennemi->next;
    }
}

 void attaquerZone(Jeu *jeu, Tourelle *tourelle)
{
    Etudiant *ennemi = jeu->etudiants;

    // Parcourir tous les étudiants dans un rayon de 2 positions autour de la tourelle
    while (ennemi != NULL)
    {
        if (ennemi->ligne == tourelle->ligne &&
            abs(ennemi->position - tourelle->position) <= 2) // Rayon de 2 positions
        {
            ennemi->pointsDeVie -= 5; // Exemple : inflige 5 points de dégâts
            if (ennemi->pointsDeVie <= 0)
            {
                printf("Un ennemi a été éliminé sur la ligne %d à la position %d !\n",
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



void afficherMenu(void)
{
    printf("Construction des Tourelles:\n");
    printf("1. Tourelle de Base (%d pièces) - Dommages sur sa ligne\n", PRIX_TOURRELE_DE_BASE);
    printf("2. Tourelle Ralentisseur (%d pièces) - Ralentit les ennemis\n", PRIX_TOURRELE_RALENTISSEUR);
    printf("3. Tourelle Mine (%d pièces) - Explose au contact\n", PRIX_TOURRELE_MINE);
    printf("4. Tourelle Zone (%d pièces) - Dommages de zone\n", PRIX_TOURRELE_ZONE);
    printf("5. Tourelle Mur (%d pièces) - Grande résistance\n", PRIX_TOURRELE_MUR);
    printf("Entrez le numéro de la tourelle à placer (1-5) : ");
}

void choisirTourelle(Jeu *jeu)
{
    int choixTourelle;
    int ligne, position;

    while (jeu->cagnotte > 0)
    {
        // Vérifier si une tourelle est abordable
        if (jeu->cagnotte < 80)  // 80 est le prix minimum pour une tourelle (Mine)
        {
            printf("Votre cagnotte (%d pièces) est insuffisante pour construire une nouvelle tourelle.", jeu->cagnotte);
            break;
        }

        afficherMenu();
        scanf("%d", &choixTourelle);

        if (choixTourelle < 1 || choixTourelle > 5)
        {
            printf("Choix invalide. Veuillez entrer un numéro entre 1 et 5.");
            continue;
        }

        printf("Entrez la ligne (1-%d) : ", NOMBRE_LIGNES);
        scanf("%d", &ligne);

        printf("Entrez la position (1-%d) : ", NOMBRE_POSITIONS);
        scanf("%d", &position);

        // Vérifier si la ligne et la position sont valides
        if (ligne < 1 || ligne > NOMBRE_LIGNES || position < 1 || position > NOMBRE_POSITIONS)
        {
            printf("Position ou ligne invalide.");
            continue;
        }

        // Déterminer le type de tourelle et son prix
        int typeTourelle;
        int prixTourelle;
        switch (choixTourelle)
        {
        case 1:
            typeTourelle = TOURRELE_DE_BASE;
            prixTourelle = PRIX_TOURRELE_DE_BASE;
            break;
        case 2:
            typeTourelle = TOURRELE_RALENTISSEUR;
            prixTourelle = PRIX_TOURRELE_RALENTISSEUR;
            break;
        case 3:
            typeTourelle = TOURRELE_MINE;
            prixTourelle = PRIX_TOURRELE_MINE;
            break;
        case 4:
            typeTourelle = TOURRELE_ZONE;
            prixTourelle = PRIX_TOURRELE_ZONE;
            break;
        case 5:
            typeTourelle = TOURRELE_MUR;
            prixTourelle = PRIX_TOURRELE_MUR;
            break;
        default:
            continue;
        }

        // Vérifier si le joueur a suffisamment d'argent pour cette tourelle
        if (jeu->cagnotte < prixTourelle)
        {
            printf("Vous n'avez pas assez d'argent (%d pièces) pour cette tourelle (prix : %d).", jeu->cagnotte, prixTourelle);
            continue;
        }

        // Créer et placer la tourelle
        Tourelle *nouvelleTourelle = creerTourelle(ligne, position, typeTourelle);
        jeu->cagnotte -= prixTourelle;
        nouvelleTourelle->next = jeu->tourelles;
        jeu->tourelles = nouvelleTourelle;

        printf("Tourelle placée avec succès à la ligne %d et position %d. Cagnotte restante : %d pièces.", ligne, position, jeu->cagnotte);
    }

    if (jeu->cagnotte == 0)
    {
        printf("Cagnotte épuisée !");
    }
}
