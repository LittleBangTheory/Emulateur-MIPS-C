#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "../headers/get_from_instruction.h"



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


void getOpCode(char* instruction, char* opcode) {

    char commande[TAILLE_MAX];
    int i = 0;

    //Détermine le premier mot de la ligne c'est à dire l'instruction
    for (i=0; instruction[i] != ' '; i++) {
        commande[i] = instruction[i];
    }
    commande[i] = '\0';

    
    if (!strcmp(commande, "ADD")) sprintf(opcode, "%s", "100000");
    else if (!strcmp(commande, "AND")) sprintf(opcode, "%s", "100100");
    else if (!strcmp(commande, "BGTZ")) sprintf(opcode, "%s", "000111");
    else if (!strcmp(commande, "BNE")) sprintf(opcode, "%s", "000101");
    else if (!strcmp(commande, "JAL")) sprintf(opcode, "%s", "000011");
    else if (!strcmp(commande, "LW")) sprintf(opcode, "%s", "100011");
    else if (!strcmp(commande, "MFLO")) sprintf(opcode, "%s", "010010");
    else if (!strcmp(commande, "SLL")) sprintf(opcode, "%s", "000000");
    else if (!strcmp(commande, "SRL")) sprintf(opcode, "%s", "000010");
    else if (!strcmp(commande, "SLT")) sprintf(opcode, "%s", "101010");
    else if (!strcmp(commande, "SUB")) sprintf(opcode, "%s", "100010");
    else if (!strcmp(commande, "ADDI")) sprintf(opcode, "%s", "001000");
    else if (!strcmp(commande, "BEQ")) sprintf(opcode, "%s", "000100");
    else if (!strcmp(commande, "BLEZ")) sprintf(opcode, "%s", "000110");
    else if (!strcmp(commande, "DIV")) sprintf(opcode, "%s", "011010");
    else if (!strcmp(commande, "J")) sprintf(opcode, "%s", "000010");
    else if (!strcmp(commande, "JR")) sprintf(opcode, "%s", "001000");
    else if (!strcmp(commande, "LUI")) sprintf(opcode, "%s", "001111");
    else if (!strcmp(commande, "MFHI")) sprintf(opcode, "%s", "010000");
    else if (!strcmp(commande, "MULT")) sprintf(opcode, "%s", "011000");
    else if (!strcmp(commande, "OR")) sprintf(opcode, "%s", "100101");
    else if (!strcmp(commande, "SW")) sprintf(opcode, "%s", "101011");
    else if (!strcmp(commande, "XOR")) sprintf(opcode, "%s", "100110");
    else if (!strcmp(commande, "ROTR")) sprintf(opcode, "%s", "000010");
    else {printf("Instruction non reconnue\n"); exit(EXIT_FAILURE);}

}


int getIArgs(char* instruction, int arg) {

    int i=0, res=0, tmp;
    char* lui = strstr(instruction, "LUI"); //Cas particulier de l'instruction LUI
    switch (arg) {
        case RT: tmp = -1; break;
        case RS: tmp = -2; break;
        case IMMEDIATE: {
            if (lui != NULL) {
                tmp = -2;
            } else {
                tmp = -3; 
            }
            break;
        }
        default: tmp = 0;
    }


    // Si on veut RT, alors on prend la valeur apres le 1er #
    // Si on veut RS, alors on prend la valeur apres le 2eme #
    // Si on veut IMMEDIATE, on prend la dernière valeur


    /*Pour le cas avec les parentheses, regarder si instruction[i+2] ou instruction de[1+3] = ')'
    Si c'est le cas, mettre i a 0 et tmp a -1, et ensuite lire la valeur de IMMEDIATE jusqu'a une valeur non numérique*/

    while (instruction[i]!='\0' && tmp<0) {
        if (instruction[i]=='$' && ((instruction[i+2]-'0')<0 || (instruction[i+2]-'0')>9)) { 
            //Cas ou la valeur est inférieure a 10
            res = instruction[i+1] - '0'; //Convertit instruction[i+1] en int
            tmp++;
        } else if (instruction[i]=='$' && ((instruction[i+2]-'0')>=0 || (instruction[i+2]-'0')<=9)) {
            //Cas ou la valeur est supérieure a 10
            res = (10*(instruction[i+1]-'0')) + (instruction[i+2]-'0');
            tmp++;
        } else if (instruction[i]==' ' && tmp==-1 && arg==IMMEDIATE) {
            res = 0;
            if (instruction[i+1] != '-') { //Cas ou IMMEDIATE est positif 
                for (int j=i+1; instruction[j]!='\0'; j++) { 
                    res += (instruction[j] - '0');
                    res *= 10;
                }
                res /= 10;
            } else { //Cas ou IMMEDIATE est négatif
                for (int j=i+2; instruction[j]!='\0'; j++) { //On commence a i+2 pour ne pas lire le moins 
                    res += (instruction[j] - '0');
                    res *= 10;
                }
                res /= 10;
                res *= -1; //On change le signe de res
            }
            tmp++;
        }
        i++;
    }

    //Opérandes non valides
    if (((arg==RT || arg==RS) && (res>31 || res<0)) || (arg==IMMEDIATE && res>65535)) {
        printf("Valeur des opérandes non valide\n");
        exit(EXIT_FAILURE);
    }

    return res;
}


int getJArgs(char* instruction) {

    int target=0, res=0;

    for (int i=0; instruction[i] != '\0'; i++) {
        if (instruction[i]==' ') {
            target = 1;
        }
        else if (target==1) {
            res += (instruction[i] - '0');
            res *= 10;
        }
    }
    res /= 10;

    //Opérandes non valides
    if (res > 67108863) {
        printf("Valeur des opérandes non valide\n");
        exit(EXIT_FAILURE);
    }

    return res;
}


int getRArgs(char* instruction, int arg) {
    int i=0, res=0, tmp;
    switch (arg) {
        case RD: tmp = -1; break;
        case RS: tmp = -2; break;
        case RT: tmp = -3; break;
        case SA: tmp = -3; break;
        default: tmp = 0;
    }


    // Si on veut RD, alors on prend la valeur apres le 1er #
    // Si on veut RS, alors on prend la valeur apres le 2eme #
    // Si on veut RT, on prend la valeur apres le 3eme #

    while (instruction[i]!='\0' && tmp<0) {
        if (instruction[i]=='$' && (instruction[i+2]==',' || instruction[i+2]<48 || instruction[i+2]>57)) {
            //Cas ou la valeur est inférieure a 10
            res = instruction[i+1] - '0'; //Convertit instruction[i+1] en int
            tmp++;
        } else if (instruction[i]=='$' && instruction[i+2]!=',') {
            //Cas ou la valeur est supérieure a 10
            res = (10*(instruction[i+1]-'0')) + (instruction[i+2]-'0');
            tmp++;
        } else if (instruction[i]==' ' && tmp==-1 && arg==SA) {
            res = 0;
            for (int j=i+1; instruction[j]!='\0'; j++) {
                res += (instruction[j] - '0');
                res *= 10;
            }
            res /= 10;
            tmp++;
        }
        i++;
    }

    //Opérandes non valides
    if (res>31 || res<0) {
        printf("Valeur des opérandes non valide\n");
        exit(EXIT_FAILURE);
    }

    return res;
}