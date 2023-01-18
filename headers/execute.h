#ifndef EXECUTE_H
#define EXECUTE_H

#define NB_REGISTRE 34
//On rajoute les registres 32 et 33 pour LO et HI
#define zero 0
#define LO 32
#define HI 33
#include "../headers/memoire.h"
#include "../headers/save_instruction.h"

void define_registers(int*);
void fill_instructions(char*, stored_instruction**, memoire*, int*);
void execute(char*, int*, int*, int*, int*, memoire*);

#endif