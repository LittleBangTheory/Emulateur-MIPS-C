#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void automatique(char* file_programme, char* file_sortie_assemblage, char* file_sortie_execution) {
    printf("Mode automatique\n");

    char instruction[TAILLE_MAX];
    char instruction_hexa[TAILLE_MAX];

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

    //Lecture du fichier
    fgets(instruction, TAILLE_MAX, programme);
    printf("%s\n", instruction);
    convert_hexa(instruction, instruction_hexa);
    printf("%s\n", instruction_hexa);
    
    fclose(programme);
    fclose(sortie_assemblage);
    fclose(sortie_execution);
}