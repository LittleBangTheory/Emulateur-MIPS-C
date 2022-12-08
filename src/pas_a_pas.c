#include <stdio.h>
#include <stdlib.h>
#include "../headers/pas_a_pas.h"
#include "../headers/read_and_convert.h"

#include "../headers/get_from_instruction.h"

void pas_a_pas(char* file_programme) {
    printf("Mode pas à pas\n");

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
        printf("%s\n", instruction);
        convert_hexa(instruction, instruction_hexa);
        printf("%s\n", instruction_hexa);

        printf("%d\n", getIArgs(instruction, RS));

        printf("Press enter to continue");
        enter = scanf("%c", &enter);
    }


    fclose(programme);
}