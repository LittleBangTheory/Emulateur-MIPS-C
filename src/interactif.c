#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/interactif.h"
#include "../headers/read_and_convert.h"
#include "../headers/execute.h"


void interactif() {
    printf("Mode interactif\n");

    //Instructions rentrées par l'utilisateur
    char instruction[TAILLE_MAX];
    char instruction_hexa[TAILLE_MAX];
    int scanf_return;

    //Initialisation listes chainées mémoire et instructions
    stored_memory* memoire = NULL;
    stored_instruction* liste_instruction = NULL;
    char* commande = malloc(sizeof(char)*6); 
    int arg1, arg2, arg3, line_number=0;
    stored_instruction* current = NULL;

    //Initialisation registres
    long int registre[NB_REGISTRE];
    define_registers(registre);

    printf("Entrez une instruction: ");
    scanf_return = scanf(" %[^\n]", instruction);
    while(strcmp(instruction, "EXIT")){
        //Lecture de l'instruction
        if (scanf_return == EOF) {
            printf("Erreur de lecture de l'instruction");
            exit(EXIT_FAILURE);
        }

        //initialisation de current
        if (current == NULL) {
            current = liste_instruction;
        }

        //conversion en hexa
        convert_hexa(instruction, instruction_hexa);
        printf("Instruction hexa : %s\n", instruction_hexa);

        //Ajout de l'instruction dans la liste chainée
        if (instruction[0] >= 65 && instruction[0] <= 90) {
            get_args(instruction, &commande, &arg1, &arg2, &arg3);
            add_instruction(commande, arg1, arg2, arg3, line_number, &liste_instruction);
            line_number++;
        }

        //Execution de l'instruction
        execute(current, registre, &memoire);
        if (current->next != NULL) {
            current = current->next;
        }        
        printMemory(memoire);

        //Lecture de la prochaine instruction
        printf("Entrez une instruction: ");
        scanf_return = scanf(" %[^\n]", instruction);
    }

    //Libération de la mémoire
    free(commande);
    clear_instructions(&liste_instruction);
    clearMemory(&memoire);
}