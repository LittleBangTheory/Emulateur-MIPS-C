#include <stdio.h>
#include <stdlib.h>
#include "../headers/save_instruction.h"

void add_instruction(char* command, int arg1, int arg2, int arg3, stored_instruction *current){
    stored_instruction *new_instruction = malloc(sizeof(stored_instruction));
    //malloc de *stored_instruction, pas stored_instruction, à remplacer 
    
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
    while (current->prev != NULL){
        printf("stored_instruction :%s %d %d %d", current->command, current->arg1, current->arg2, current->arg3);
        current = current->prev;
    }
}

void branch(stored_instruction *current, int branch_value){
    current = current->next;
    //execute(current->command, current->arg1, current->arg2, current->arg3, registre, memoire);
    //erreur au dessus parce que execute n'est pas terminé, et registre et mémoire pas passés en paramètre de ce fichier
    for (int i = 0; i < branch_value; i++){
        current = current->next;
    }
}

void jump(stored_instruction *current, int line_number){
    int i = 0;
    //a vérifier si jump aussi execute l'instruction à pc+4 avant de sauter
    while (i < line_number){
        current = current->next;
        i++;
    }
}
