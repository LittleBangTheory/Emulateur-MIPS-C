#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/pas_a_pas.h"
#include "../headers/read_and_convert.h"
#include "../headers/save_instruction.h"
#include "../headers/get_from_instruction.h"
#include "../headers/execute.h"


void pas_a_pas(char* file_programme) {
    char instruction[TAILLE_MAX];
    //char instruction_hexa[TAILLE_MAX];
    char enter;

    FILE* programme;

    programme = fopen(file_programme, "r");

    if (programme==NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(EXIT_FAILURE);
    } 

    //Initialisation de la mémoire et de la liste des instructions
    memoire* memoire = NULL;
    struct instruction* liste_instruction = NULL;
    

    //Lecture du fichier
    int registre[NB_REGISTRE];
    define_registers(registre);
    while (fgets(instruction, TAILLE_MAX, programme) != NULL) {
        if (instruction[0] >= 65 && instruction[0] <= 90) {
            printf("Instruction rentrée : %s\n", instruction);
            //convert_hexa(instruction, instruction_hexa);
            //printf("%s\n", instruction_hexa);

            fill_instructions(instruction, &liste_instruction, memoire, registre);
            //printMemory(memoire);

            printf("Press enter to continue");
            enter = scanf("%c", &enter);
        }
    }
    afficher_instructions(liste_instruction);
    clear_instructions(&liste_instruction);


    fclose(programme);
}