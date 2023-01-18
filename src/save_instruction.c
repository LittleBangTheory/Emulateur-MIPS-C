#include <stdio.h>
#include <stdlib.h>
#include "../headers/save_instruction.h"

void add_instruction(char* command, int arg1, int arg2, int arg3, stored_instruction **current){

    stored_instruction* suivant = *current;
    stored_instruction* new_instruction;

    if ((new_instruction = malloc(sizeof(stored_instruction))) == NULL) {
        printf("Errur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    if (suivant == NULL) {
        *current = new_instruction;
        new_instruction->command = command;
        new_instruction->arg1 = arg1;
        new_instruction->arg2 = arg2;
        new_instruction->arg3 = arg3;
        new_instruction->next = NULL;
        new_instruction->prev = NULL;
    } else {
        while (suivant->next != NULL) {
            suivant = suivant->next;
        }

        suivant->next = new_instruction;
        new_instruction->command = command;
        new_instruction->arg1 = arg1;
        new_instruction->arg2 = arg2;
        new_instruction->arg3 = arg3;
        new_instruction->next = NULL;
        new_instruction->prev = suivant;
    }

    /*
    stored_instruction *new_instruction = malloc(sizeof(stored_instruction));
    
    new_instruction->command = command;
    new_instruction->arg1 = arg1;
    new_instruction->arg2 = arg2;
    new_instruction->arg3 = arg3;
    new_instruction->next = NULL;
    new_instruction->prev = NULL;

    if (current == NULL){
        current = new_instruction;

    }
    else{
        current->next = new_instruction;
        new_instruction->prev = current;
        current = new_instruction;
    }
    */
}

void delete_instructions(stored_instruction* last_instruction){
    stored_instruction* current = last_instruction;
    stored_instruction* prev = NULL;

    while (current != NULL){
        prev = current->prev;
        free(current);
        current = prev;
    }
}

void afficher_instructions(stored_instruction* last_instruction){
    stored_instruction* current = last_instruction;
    if (current == NULL){
        printf("No instruction to display\n");
    }
    while (current != NULL){
        printf("Stored_instruction :%s %d %d %d\n", current->command, current->arg1, current->arg2, current->arg3);
        current = current->next;
    }
}

void clear_instructions(stored_instruction **instruction) {
    stored_instruction *tmp = *instruction;
    stored_instruction *tmp2 = NULL;
    while (tmp != NULL) {
        tmp2 = tmp->next;
        free(tmp);
        tmp = tmp2;
    }
    *instruction = NULL;
}

void branch(stored_instruction *current, int branch_value){
    current = current->next;
    //(a cause de l'erreur) execute(current->command, current->arg1, current->arg2, current->arg3, registre, memoire);
    for (int i = 0; i < branch_value; i++){
        current = current->next;
    }
}

void jump(stored_instruction *current, int line_number){
    int i = 0;
    while (i < line_number){
        current = current->next;
        i++;
    }
}
