#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/interactif.h"
#include "../headers/read_and_convert.h"


void interactif() {
    printf("Mode interactif\n");

    char instruction[TAILLE_MAX];
    char instruction_hexa[TAILLE_MAX];
    int scanf_return;

   
     scanf_return = scanf(" %[^\n]", instruction);
     while(strcmp(instruction, "EXIT")) {
        if (scanf_return == EOF) {
            printf("Erreur de lecture\n");
            exit(EXIT_FAILURE);
        }
        convert_hexa(instruction, instruction_hexa);
        printf("%s\n", instruction_hexa);
        scanf_return = scanf(" %[^\n]", instruction);
   }

}