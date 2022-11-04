#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void convert_hexa(char* instruction, char* instruction_hexa) {

    int type = getType(instruction);

    /*
    int j=0;
    for (int i=0; instruction[i] != '\n'; i++) {
        sprintf((char*)(instruction_hexa+j), "%02X", instruction[i]);
        j+=2;
    }
    */
}


int getType(char* instruction) {
    int type;
    char commande[TAILLE_MAX];
    char* typeI[NB_TYPE_I] = {"ADDI", "LW", "SW", "LUI", "BEQ", "BNE", "BGTZ", "BLEZ"};
    char* typeJ[NB_TYPE_J] = {"J", "JAL"};
    char* typeR[NB_TYPE_R] = {"ADD", "SUB", "MULT", "DIV", "AND", "OR", "XOR", "ROTR", "SLL", "SRL", "SLT", "MFHI", "MFLO", "JR"};
    
    int i = 0;
    for (i=0; instruction[i] != ' '; i++) {
        commande[i] = instruction[i];
    }
    commande[i] = '\0';

    for (i=0; i < NB_TYPE_I; i++) {
        if (strcmp(commande, typeI[i]) == 0) {
            type = TYPE_I;
        }
    }

    for (i=0; i < NB_TYPE_J; i++) {
        if (strcmp(commande, typeJ[i]) == 0) {
            type = TYPE_J;
        }
    }

    for (i=0; i < NB_TYPE_R; i++) {
        if (strcmp(commande, typeR[i]) == 0) {
            type = TYPE_R;
        }
    }


    return type;
}