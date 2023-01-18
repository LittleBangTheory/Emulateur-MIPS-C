#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef struct instruction stored_instruction;
struct instruction {
    char* command;
    int arg1;
    int arg2;
    int arg3;
    stored_instruction *next;
    stored_instruction *prev;
};

void add_instruction(char*, int, int, int, stored_instruction**);
void delete_instructions(stored_instruction*);
void branch(stored_instruction*, int);
void jump(stored_instruction*, int);
void afficher_instructions(stored_instruction*);
void clear_instructions(stored_instruction **instruction);

#endif

