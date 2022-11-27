#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void pas_a_pas(char* file_programme) {
    printf("Mode automatique\n");

    char instruction[TAILLE_MAX];
    char instruction_hexa[TAILLE_MAX];
    char enter;

    FILE* programme;

    programme = fopen(file_programme, "r");

    if (programme==NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(EXIT_FAILURE);
    }

    //Lecture du fichier
    while (fgets(instruction, TAILLE_MAX, programme)[0] != '\n') {
        printf("%s", instruction);
        convert_hexa(instruction, instruction_hexa);
        printf("%s\n", instruction_hexa);
        printf("Press enter to continue");
        enter = scanf("%c", &enter);
    }


    fclose(programme);
}