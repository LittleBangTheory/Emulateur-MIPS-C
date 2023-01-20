#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "../headers/memoire.h"

typedef struct instruction stored_instruction;
struct instruction {
    char command[5];
    int arg1;
    int arg2;
    int arg3;
    int line_number;
    stored_instruction *next;
    stored_instruction *prev;
};

void add_instruction(char*, int, int, int, int, stored_instruction**);
void branch(stored_instruction**, int);
void jump(stored_instruction**, int);
void afficher_instructions(stored_instruction*);
void clear_instructions(stored_instruction **instruction);
void afficher_instruction_courrante(stored_instruction* current, FILE* sortie);

#endif

