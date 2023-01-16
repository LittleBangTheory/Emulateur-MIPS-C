#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef struct instruction instruction;
struct instruction {
    char* command;
    int arg1;
    int arg2;
    int arg3;
    instruction *next;
    instruction *prev;
};

void add_instruction(char*, int, int, int, instruction*);
void delete_instructions(instruction*);
void branch(instruction*, int);
void jump(instruction*, int);
void afficher_instructions(instruction*);

#endif

