#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "../headers/read_and_convert.h"
#include "../headers/get_from_instruction.h"


void get_args(char* instruction) {
    char commande[TAILLE_MAX];

    //Disjonction de cas des types
    char* typeR_SA[NB_TYPE_R_SA] = {"ROTR", "SLL", "SRL"};
    char* typeR_ARG1[NB_TYPE_R_ARG1] = {"JR", "MFHI", "MFLO"};
    char* typeR_ARG2[NB_TYPE_R_ARG2] = {"DIV", "MULT"};

    //typeR_ARG3 est le cas par défaut
    int typeR = ARG3;
    //On a trois arguments maximum par instruction
    int arg1, arg2, arg3;
    
    int type = getType(instruction);

    if (type == TYPE_I) {
        //on récupère les arguments
        arg1 = getIArgs(instruction, RT); //rt
        arg2 = getIArgs(instruction, RS); //rs
        arg3 = getIArgs(instruction, IMMEDIATE); //imm

    } else if (type == TYPE_J) {
        //on récupère la cible du saut
        arg1 = getJArgs(instruction); //target
        
    } else if (type == TYPE_R) {
        //On récupère la commande
        int i = 0;
        for (i=0; instruction[i] != ' '; i++) {
            commande[i] = instruction[i];
        }
        commande[i] = '\0';

        for (i=0; i < NB_TYPE_R_SA; i++) {
            if (strcmp(commande, typeR_SA[i]) == 0) {
                typeR = ARGSA;
            }
        }

        for (i=0; i < NB_TYPE_R_ARG1; i++) {
            if (strcmp(commande, typeR_ARG1[i]) == 0) {
                typeR = ARG1;
            }
        }

        for (i=0; i < NB_TYPE_R_ARG2; i++) {
            if (strcmp(commande, typeR_ARG2[i]) == 0) {
                typeR = ARG2;
            }
        }


        if (typeR == ARGSA) {
            arg1 = getRArgs(instruction, RD); //rd
            arg2 = getRArgs(instruction, RT); //rt
            arg3 = getRArgs(instruction, SA); //sa
        } else if (typeR == ARG3) {
        } else if (typeR == ARG2) {
            arg1 = getRArgs(instruction, RD); //rs
            arg2 = getRArgs(instruction, RS); //rt
        } else if (typeR == ARG1) {
            arg1 = getRArgs(instruction, RD); //rd
        } else {
            //typeR = ARG3 est le cas par défaut
            arg1 = getRArgs(instruction, RD); //rd
            arg2 = getRArgs(instruction, RT); //rt
            arg3 = getRArgs(instruction, RS); //rs
        }
    }

    execute(commande, &arg1, &arg2, &arg3);
    //on envoie la commande et les opérandes à execute
}



void execute(char* command, char* arg1, char* arg2, char* arg3) {
    //création tableau pour stocker l'état des registres 2 à 25
    //$0 et $1 sont réservés, mais on crée quand même un tableau de 0 à 25 pour plus de clarté 
    int registre[26];
    //on aurait pu créer une variable de type constant int pour le $0, mais par simplicité on utilisera directement registre[0]
    registre[0]=0;
    for (int i=1; i<26; i++) {
        //on initialise tous les registres à 32767, la valeur max du type int, pour savoir à la fin de l'exécution si un registre a été modifié
        registre[i]=32767;
    }

    //disjonction de cas pour toutes les instructions
    //code Github copilot, à reprendre
    if (strcmp(command, "ADD") == 0) {
        registre[*arg1] = registre[*arg2] + registre[*arg3];
    } else if (strcmp(command, "ADDI") == 0) {
        registre[*arg1] = registre[*arg2] + *arg3;
    } else if (strcmp(command, "ADDIU") == 0) {
        registre[*arg1] = registre[*arg2] + *arg3;
    } else if (strcmp(command, "ADDU") == 0) {
        registre[*arg1] = registre[*arg2] + registre[*arg3];
    } else if (strcmp(command, "AND") == 0) {
        registre[*arg1] = registre[*arg2] & registre[*arg3];
    } else if (strcmp(command, "ANDI") == 0) {
        registre[*arg1] = registre[*arg2] & *arg3;
    } else if (strcmp(command, "BEQ") == 0) {
        if (registre[*arg1] == registre[*arg2]) {
            //on saute à l'instruction cible
        }
    } else if (strcmp(command, "BGEZ") == 0) {
        if (registre[*arg1] >= 0) {
            //on saute à l'instruction cible
        }
    } else if (strcmp(command, "BGEZAL") == 0) {
        if (registre[*arg1] >= 0) {
            //on saute à l'instruction cible
        }
    } else if (strcmp(command, "BGTZ") == 0) {
        if (registre[*arg1] > 0) {
            //on saute à l'instruction cible
        }
    } else if (strcmp(command, "BLEZ") == 0) {
        if (registre[*arg1] <= 0) {
            //on saute à l'instruction cible
        }
    } else if (strcmp(command, "BLTZ") == 0) {
        if (registre[*arg1] < 0) {
            //on saute à l'instruction cible
        }
}
