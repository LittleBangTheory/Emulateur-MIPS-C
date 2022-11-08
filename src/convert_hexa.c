#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

void convert_hexa(char* instruction, char* instruction_hexa) {

    //int type = getType(instruction);

    //Juste pour teser convert_binaire, a supprimer
    //convert_binaire(0,5,instruction_hexa);
    //printf("%s\n", instruction_hexa);
    //printf("%d\n", getIArgs(instruction, IMMEDIATE));

    encoder(instruction, instruction_hexa);
    printf("%s\n", instruction_hexa);

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
    else if (!strcmp(commande, "SUB")) sprintf(opcode, "%s", "1000010");
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
    else sprintf(opcode, "%s", "000000");

}


void convert_binaire(int valeur, int nb_bits, char* valeur_binaire) {

    int binaryNum[32];
    int i=0, k=0;
    int nb_zeros=0;
   
    for ( ;valeur > 0; ){
        binaryNum[i++] = valeur % 2;
        valeur /= 2;
    }

    
    //Remplit le début du tableau avec des zeros pour avoir le bon nombre de bits
    if (i < nb_bits) {
        nb_zeros = nb_bits-i;
        for (k=0; k<nb_zeros; k++) {
            valeur_binaire[k] = '0';
        }
    }


    //Parcours binaryNum à l'envers pour remplir le tableau avec les bonnes valeurs dans le bon ordre apres les zeros
    for (int j=i-1; j>=0; j--) {
        sprintf((char*)(valeur_binaire+k), "%d", binaryNum[j]);
        k++;
    }

    

}


void encoder(char* instruction, char* instruction_encodee) {

    char opcode[7];
    int type;

    char rt[6], rs[6], imm[17];
    
    getOpCode(instruction, opcode);
    type = getType(instruction);

    if (type == TYPE_I) {
        convert_binaire(getIArgs(instruction, RT), 5, rt);
        convert_binaire(getIArgs(instruction, RS), 5, rs);
        convert_binaire(getIArgs(instruction, IMMEDIATE), 16, imm);
        rt[5] = '\0';
        rs[5] = '\0';
        imm[16] = '\0';

        strcat(instruction_encodee, opcode);
        strcat(instruction_encodee, rs);
        strcat(instruction_encodee, rt);
        strcat(instruction_encodee, imm);

    }
}


int getIArgs(char* instruction, int arg) {

    int i=0, res=0, tmp;
    switch (arg) {
        case RT: tmp = -1; break;
        case RS: tmp = -2; break;
        case IMMEDIATE: tmp = -3; break;
        default: tmp = 0;
    }

    while (instruction[i]!='\0' && tmp<0) {
        if (instruction[i]=='$' && instruction[i+2]==',') {
            res = instruction[i+1] - '0';
            tmp++;
        } else if (instruction[i]=='$' && instruction[i+2]!=',') {
            res = (10*(instruction[i+1]-'0')) + (instruction[i+2]-'0');
            tmp++;
        } else if (instruction[i]==' ' && tmp==-1 && arg==IMMEDIATE) {
            res = 0;
            for (int j=i+2; instruction[j]!='\0'; j++) {
                res += (instruction[j-1] - '0');
                res *= 10;
            }
            res /= 10;
            tmp++;
        }
        i++;
    }

    return res;
}
