#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "../headers/read_and_convert.h"
#include "../headers/get_from_instruction.h"
#include "../headers/execute.h"
#include "../headers/memoire.h"
#include "../headers/save_instruction.h"

/** \file execute.c 
*   \brief Fichier contenant les fonctions d'exécution des instructions
*/


/** \fn void define_registers(long int* registre)
*   \brief Fonction qui initialise tous les registres à 0
*   \param registre Tableau de registres créé dans le fichier de mode
*/
void define_registers(long int* registre) {
    //on aurait pu créer une variable de type constant int pour le $0, mais par simplicité on utilisera directement registre[0]
    for (int i=0; i<NB_REGISTRE; i++) {
        //on initialise tous les registres à 0, pour savoir à la fin de l'exécution si un registre a été modifié
        registre[i]=0;
    }
}

/** \fn void get_args(char* instruction, char** commande, int* arg1, int* arg2, int* arg3)
*   \brief Fonction qui récupère les arguments et la commande d'une instruction
*   \param instruction Chaine de caractère contenant l'instruction à découper
*   \param commande Pointeur sur la chaine de caractère contenant la commande
*   \param arg1 Pointeur sur l'entier contenant le premier argument
*   \param arg2 Pointeur sur l'entier contenant le deuxième argument
*   \param arg3 Pointeur sur l'entier contenant le troisième argument
*/
void get_args(char* instruction, char** commande, int* arg1, int* arg2, int* arg3) {
    int args[3];
    int i = 0;

    const char* separators = " ,()$\n";
    char* token = strtok(instruction, separators);
    while (token != NULL && i<4) {
        if (i == 0) {
            //on récupère la commande
            strcpy(*commande, token);
        } else {
            //on récupère les opérandes
            args[i-1] = atoi(token);
        }
        token = strtok(NULL, separators);
        i++;
    }

    *arg1 = args[0];
    *arg2 = args[1];
    *arg3 = args[2];

    //pour savoir si un argument a été modifié, par exemple pour ne pas afficher arg2 et arg3 pour une instruction J
    for (int i=0; i<3; i++) {
        args[i] = -32768;
    }
}


/** \fn void execute(stored_instruction** instruction, long int* registre, stored_memory** memoire, FILE* sortie_affichage)
*   \brief Fonction qui exécute une instruction passée en paramètre
*   \param instruction Pointeur de pointeur sur l'instruction à exécuter
*   \param registre Tableau de registres créé dans le fichier de mode
*   \param memoire Pointeur de pointeur sur la mémoire créée dans le fichier de mode
*   \param sortie_affichage Pointeur sur le fichier de sortie d'affichage
*   Analyse l'élément de liste chainée passé en paramètre, récupère les arguments et la commande, puis exécute l'instruction
*   Les instructions de type branch ou jump font appel respectivement aux fonctions void branch et void jump 
*/
void execute(stored_instruction** instruction, long int* registre, stored_memory** memoire, FILE* sortie_affichage) {
    //Affichage de l'instruction
    afficher_instruction_courrante(*instruction, sortie_affichage);

    char* command = malloc(sizeof((*instruction)->command));
    strcpy(command, (*instruction)->command);
    int arg1 = (*instruction)->arg1;
    int arg2 = (*instruction)->arg2;
    int arg3 = (*instruction)->arg3;
    //disjonction de cas pour toutes les (*instruction)s
    if (strcmp(command, "ADD") == 0) {
        registre[arg1] = registre[arg2] + registre[arg3];
    } else if (strcmp(command, "ADDI") == 0) {
        registre[arg1] = registre[arg2] + arg3;
    } else if (strcmp(command, "AND") == 0) {
        registre[arg1] = registre[arg2] & registre[arg3];
    }
    //Branch 
    else if (strcmp(command, "BEQ") == 0) {
        if (registre[arg1] == registre[arg2]) {
            (*instruction) = (*instruction)->next;
            execute(instruction, registre, memoire, sortie_affichage);
            if (arg3 == 0){
                execute(instruction, registre, memoire, sortie_affichage);
            } else {
                branch(instruction, arg3);
            }
        }
    } else if (strcmp(command, "BLEZ") == 0) {
        if (registre[arg1] <= 0) {
            (*instruction) = (*instruction)->next;
            execute(instruction, registre, memoire, sortie_affichage);
            if (arg2 == 0){
                execute(instruction, registre, memoire, sortie_affichage);
            } else {
                branch(instruction, arg2);
            }
    }
    } else if (strcmp(command, "BGTZ") == 0) {
        if (registre[arg1] > 0) {
            (*instruction) = (*instruction)->next;
            execute(instruction, registre, memoire, sortie_affichage);
            if (arg2 == 0){
                execute(instruction, registre, memoire, sortie_affichage);
            } else {
                branch(instruction, arg2);
            }
        }
    } else if (strcmp(command, "BNE") == 0) {
        if (registre[arg1] != registre[arg2]) {
            (*instruction) = (*instruction)->next;
            execute(instruction, registre, memoire, sortie_affichage);
            if (arg3 == 0){
                execute(instruction, registre, memoire, sortie_affichage);
            } else {
                branch(instruction, arg3);
            }
            
        }
    } 
    //Div
    else if(strcmp(command, "DIV") == 0){
        if (registre[arg2] == 0){
            printf("Erreur : division par 0\n");
            exit(EXIT_FAILURE);
        } else {
            registre[HI]=registre[arg1]/registre[arg2];
            registre[LO]=registre[arg1]%registre[arg2];
        }
    }
    //Jump
    else if(strcmp(command, "J") == 0){
        (*instruction) = (*instruction)->next;
        execute(instruction, registre, memoire, sortie_affichage);
        jump(instruction, arg1);
    } else if(strcmp(command, "JAL") == 0){
        (*instruction) = (*instruction)->next;
        registre[ra] = ((*instruction)->next)->line_number;
        execute(instruction, registre, memoire, sortie_affichage);
        jump(instruction, arg1);
    } else if(strcmp(command, "JR") == 0){
        (*instruction) = (*instruction)->next;
        execute(instruction, registre, memoire, sortie_affichage);
        jump(instruction, registre[arg1]);
    }
    //Load 
    else if(strcmp(command, "LUI") == 0){
        registre[arg1] = arg3 << 16;
    } else if(strcmp(command, "LW") == 0){
        loadElement(memoire, arg2 + registre[arg3], &registre[arg1]);    
    } 
    //Move
    else if(strcmp(command, "MFHI") == 0){
        registre[arg1] = registre[HI];
    } else if(strcmp(command, "MFLO") == 0){
        registre[arg1] = registre[LO];
    } 
    //Mult
    else if(strcmp(command, "MULT") == 0){
        if (registre[arg1]*registre[arg2] < 2147483647 && registre[arg1]*registre[arg2]> -2147483648) {
            /*registre[HI] = (((1 << 32) - 1) << 32 ) & (registre[arg1]*registre[arg2]);
            registre[LO] = ((1 << 32) - 1) & registre[arg1]*registre[arg2];*/
            unsigned long int left_part=18446744069414584320;
            //18446744069414584320 est 1 [63;32] puis 0 sur [31;0] en hexa
            long int right_part=4294967295;
            //4294967295 est 0 [63;32] puis 1 sur [31;0] en hexa
            registre[HI] = ((registre[arg1] * registre[arg2]) & left_part) >> 32; 
            registre[LO] = ((registre[arg1] * registre[arg2]) & right_part);
        } else {
            printf("Overflow, on ignore le résultat\n");
        }
    } 
    //Or
    else if(strcmp(command, "OR") == 0){
        registre[arg1] = registre[arg2] | registre[arg3];
    } 
    //Rotate
    else if(strcmp(command, "ROTR") == 0){
        unsigned arg2tmp = (unsigned long int)registre[arg2];
        unsigned arg3tmp = (unsigned long int)arg3;
        registre[arg1] = (arg2tmp >> arg3tmp) | (arg2tmp << (32 - arg3tmp));
    }
    //Shift 
    else if(strcmp(command, "SLL") == 0){
        registre[arg1] = registre[arg2] << arg3;    
    } else if(strcmp(command, "SRL") == 0){
        registre[arg1] = registre[arg2] >> arg3;
    }  
    //Set on less than
    else if(strcmp(command, "SLT") == 0){
        if (registre[arg2] < registre[arg3]) {
            registre[arg1] = 1;
        } else {
            registre[arg1] = 0;
        }
    } 
    //Sub
    else if(strcmp(command, "SUB") == 0){
        registre[arg1] = registre[arg2] - registre[arg3];
    } 
    //Store
    else if(strcmp(command, "SW") == 0){
        storeElement(memoire, registre[arg1], registre[arg3] + arg2);
    } 
    //Exclusive OR
    else if(strcmp(command, "XOR") == 0){
        registre[arg1] = registre[arg2] ^ registre[arg3];
    } else if (strcmp(command, "NOP") == 0) {
        //On ne fait rien
    } else {
        printf("Erreur : commande inconnue\n");
    }
    free(command);

    //Affichage des registres
    afficherRegistres(registre, sortie_affichage);
}

/** \fn void afficherRegistres(long int* registre, FILE* sortie)
*   \brief Affiche les registres modifiés
*   \param registre Tableau des registres
*   \param sortie Fichier de sortie
*   Affiche les registres non nuls, et les registres HI et LO si au moins l'un des deux n'est pas nul
*/
void afficherRegistres(long int* registre, FILE* sortie) {
    if (sortie != NULL) {
        for (int i=0; i<NB_REGISTRE-2; i++) {
            if (registre[i] != 0) {
                fprintf(sortie, "$%d:%ld\n", i, registre[i]);
            }
        }
        if(registre[HI] != 0 || registre[LO] != 0) {
            fprintf(sortie, "HI:%ld\n", registre[HI]);
            fprintf(sortie, "LO:%ld\n", registre[LO]);
        }
    }
}
