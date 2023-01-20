#ifndef EXECUTE_H
#define EXECUTE_H

#define NB_REGISTRE 34
//On rajoute les registres 32 et 33 pour LO et HI
#define zero 0
#define HI 32
#define LO 33
#include "../headers/memoire.h"
#include "../headers/save_instruction.h"

void define_registers(long int*);
void get_args(char*, char**, int*, int*, int*);
void execute(stored_instruction* instruction, long int* registre, stored_memory** memoire);
void afficherRegistres(long int* registre, FILE* sortie);

#endif