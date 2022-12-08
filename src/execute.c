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

    int* type, rt, rs, imm, rd, sa, target;
    
    *type = getType(instruction);

    if (type == TYPE_I) {
        //on récupère les arguments
        getIArgs(instruction, RT), 5, rt;
        getIArgs(instruction, RS), 5, rs;
        getIArgs(instruction, IMMEDIATE), 16, imm;

    } else if (type == TYPE_J) {
        //on récupère la cible du saut
        getJArgs(instruction), 26, target;
        
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
            getRArgs(instruction, RD), 5, rd;
            getRArgs(instruction, RT), 5, rt;
            getRArgs(instruction, SA), 5, sa;
        } else if (typeR == ARG3) {
        } else if (typeR == ARG2) {
            getRArgs(instruction, RD), 5, rs;
            getRArgs(instruction, RS), 5, rt;
        } else if (typeR == ARG1) {
            getRArgs(instruction, RD), 5, rd;
        } else {
            //typeR = ARG3 est le cas par défaut
            getRArgs(instruction, RD), 5, rd;
            getRArgs(instruction, RT), 5, rt;
            getRArgs(instruction, RS), 5, rs;
        }
    }

    //on envoie la commande et les opérandes à execute
}


/*
void execute(char* command, char* arg1, char* arg2, char* arg3) {
    //création tableau pour stocker l'état des ? registres
    //disjonction de cas pour toutes les instructions
}
*/