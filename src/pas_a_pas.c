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
    stored_memory* memoire = NULL;
    stored_instruction* liste_instruction = NULL;

    char* commande = malloc(sizeof(char)*5);
    int arg1, arg2, arg3, line_number=0;
    
    //Initialisation des registres
    long int registre[NB_REGISTRE];
    define_registers(registre);

    //Lecture du fichier
    while (fgets(instruction, TAILLE_MAX, programme) != NULL) {
        if (instruction[0] >= 65 && instruction[0] <= 90) {
            //printf("Instruction rentrée : %s\n", instruction);
            //convert_hexa(instruction, instruction_hexa);
            //printf("%s\n", instruction_hexa);

            get_args(instruction, &commande, &arg1, &arg2, &arg3);
            add_instruction(commande, arg1, arg2, arg3, line_number, &liste_instruction);
            line_number++;
        }
    }

    //Execution du programme
    stored_instruction* current = liste_instruction;
    while (current != NULL){
        afficher_instruction_courrante(current);
        execute(current, registre, &memoire);

        afficherRegistres(registre);

        printf("Press enter to continue\n");
        enter = scanf("%c", &enter);

        current = current->next;
    }



    free(commande);
    clear_instructions(&liste_instruction);
    clearMemory(&memoire);
    fclose(programme);
}