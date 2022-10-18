#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void automatique(char* file_programme, char* file_sortie_assemblage, char* file_sortie_execution) {
    printf("Mode automatique\n");

    FILE* programme;
    FILE* sortie_assemblage;
    FILE* sortie_execution;

    programme = fopen(file_programme, "r");
    sortie_assemblage = fopen(file_sortie_assemblage, "w");
    sortie_execution = fopen(file_sortie_execution, "w");

    if (programme==NULL || sortie_assemblage==NULL || sortie_execution==NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(EXIT_FAILURE);
    }

    
    fclose(programme);
    fclose(sortie_assemblage);
    fclose(sortie_execution);
}