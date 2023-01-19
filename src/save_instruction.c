#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/save_instruction.h"
#include "../headers/memoire.h"
#include "../headers/execute.h"

void add_instruction(char* command, int arg1, int arg2, int arg3, int line_number, stored_instruction **current){

    stored_instruction* suivant = *current;
    stored_instruction* new_instruction = malloc(sizeof(stored_instruction));

    if (new_instruction == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    if (suivant == NULL) {
        *current = new_instruction;
        strcpy(new_instruction->command, command);
        new_instruction->arg1 = arg1;
        new_instruction->arg2 = arg2;
        new_instruction->arg3 = arg3;
        new_instruction->line_number = line_number;
        new_instruction->next = NULL;
        new_instruction->prev = NULL;
    } else {
        while (suivant->next != NULL) {
            suivant = suivant->next;
        }

        suivant->next = new_instruction;
        strcpy(new_instruction->command, command);
        new_instruction->arg1 = arg1;
        new_instruction->arg2 = arg2;
        new_instruction->arg3 = arg3;
        new_instruction->line_number = line_number;
        new_instruction->next = NULL;
        new_instruction->prev = suivant;
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

void afficher_instruction_courrante(stored_instruction* current) {
    printf("Stored_instruction :%s %d %d %d\n", current->command, current->arg1, current->arg2, current->arg3);
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

void branch(stored_instruction *current, int branch_value, long int* registre, stored_memory* memoire){
    current = current->next;
    execute(current, registre, &memoire);
    int i = 0;
    if (branch_value < -1){  
        while (i < branch_value-2 && current->next != NULL){
            current = current->next;
            i++;
            if (current->next == NULL){
                printf("Error : branch value is too low\n");
                exit(EXIT_FAILURE);
            }
        }
    } else if (branch_value > 1) {
        while(i > branch_value && current->prev != NULL){
            current = current->prev;
            i--;
            if (current->prev == NULL){
                printf("Error : branch value is too high\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

void jump(stored_instruction* current, int line_number){
    if (line_number > current->line_number){  
        while (line_number > current->line_number && current->next != NULL){
            current = current->next;
            if (current->next == NULL){
                printf("Error : branch value is too high\n");
                exit(EXIT_FAILURE);
            }
        }
    } else {
        while(line_number < current->line_number && current->prev != NULL){
            current = current->prev;
            if (current->prev == NULL){
                printf("Error : branch value is too low\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
