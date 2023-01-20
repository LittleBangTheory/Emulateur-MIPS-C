/** \file save_instruction.h
 *  \brief Fichier contenant les prototypes des fonctions de save_instruction.c 
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "../headers/memoire.h"

/** \struct instruction
 *  \brief Structure de la liste des instructions
 *  \param command Commande de l'instruction, sur 5 caractères (dont la sentinelle)
 *  \param arg1 Premier argument de l'instruction 
 *  \param arg2 Deuxième argument de l'instruction
 *  \param arg3 Troisième argument de l'instruction
 *  \param line_number Numéro de la ligne de l'instruction
 *  \param next Pointeur vers l'instruction suivante (NULL si c'est la dernière instruction)
 *  \param prev Pointeur vers l'instruction précédente (NULL si c'est la première instruction)
*/
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

