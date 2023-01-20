/** \file execute.h
 *  \brief Fichier contenant les prototypes des fonctions de execute.c * 
*/


#ifndef EXECUTE_H
#define EXECUTE_H

/** \def NB_REGISTRE
 *  \brief Définition du nombre de registres (32 + 2 pour HI et LO) 
*/
#define NB_REGISTRE 34
//On rajoute les registres 32 et 33 pour LO et HI

/** \def zero
 *  \brief Définition du registre zero (registre 0)
 *  \def ra
 *  \brief Définition du registre ra (registre 31)
 *  \def HI
 *  \brief Définition du registre HI (registre 32)
 *  \def LO
 *  \brief Définition du registre LO (registre 33)
*/
#define zero 0
#define ra 31
#define HI 32
#define LO 33
#include "../headers/memoire.h"
#include "../headers/save_instruction.h"

void define_registers(long int*);
void get_args(char*, char**, int*, int*, int*);
void execute(stored_instruction** instruction, long int* registre, stored_memory** memoire, FILE* sortie_affichage);
void afficherRegistres(long int* registre, FILE* sortie);

#endif