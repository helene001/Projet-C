#include <stdio.h>
#include <stdlib.h>
#include "struct_etud.h"

Liste* placer(char * nom_fichier){
FILE* fichierMechant = NULL;
fichierMechant = fopen(nom_fichier, "r");
if (fichierMechant == NULL) {
    printf("Erreur lors de l'ouverture du fichier");
    exit(1);
}

Liste*l=malloc(7*sizeof(Liste));
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
fscanf(fichierMechant, "%d", &header);
while (fscanf(fichierMechant, "%d %d %c", &tour, &ligne, &type) == 3) {
    creer_etu(type,ligne,tour,l);
    }

fclose(fichierMechant);

return l;

}
