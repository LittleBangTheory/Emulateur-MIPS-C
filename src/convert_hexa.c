#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "header.h"

void convert_hexa(char* instruction, char* instruction_hexa) {

    int i=0, dec_val=0, taille_instruction_encodee;
    char instruction_encodee[500];

    encoder(instruction, instruction_encodee);

    //Trouver la taille de la chaine
    taille_instruction_encodee = strlen(instruction_encodee);
    
    //Convertir le binaire en hexa
    for (int j=taille_instruction_encodee-1; j>=0; j--) {
        dec_val += (instruction_encodee[j] - '0')*pow(2, taille_instruction_encodee-j-1);
    }
    sprintf(instruction_hexa, "%.8x\n", dec_val);
    
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

    char commande[TAILLE_MAX];
    char* typeR_SA[NB_TYPE_R_SA] = {"ROTR", "SLL", "SRL"};
    char* typeR_ARG1[NB_TYPE_R_ARG1] = {"JR", "MFHI", "MFLO"};
    char* typeR_ARG2[NB_TYPE_R_ARG2] = {"DIV", "MULT"};
    int typeR = ARG3;

    char opcode[7];
    int type;

    char rt[6], rs[6], imm[17], rd[6], sa[6];

    char target[27];
    
    getOpCode(instruction, opcode);
    type = getType(instruction);

    if (type == TYPE_I) {
        convert_binaire(getIArgs(instruction, RT), 5, rt);
        convert_binaire(getIArgs(instruction, RS), 5, rs);
        convert_binaire(getIArgs(instruction, IMMEDIATE), 16, imm);
        rt[5] = '\0';
        rs[5] = '\0';
        imm[16] = '\0';

        strcpy(instruction_encodee, opcode);
        strcat(instruction_encodee, rs);
        strcat(instruction_encodee, rt);
        strcat(instruction_encodee, imm);

    } else if (type == TYPE_J) {
        convert_binaire(getJArgs(instruction), 26, target);
        target[26] = '\0';
        strcpy(instruction_encodee, opcode);
        strcat(instruction_encodee, target);
        
    } else if (type == TYPE_R) {
        
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
            convert_binaire(getRArgs(instruction, RD), 5, rd);
            convert_binaire(getRArgs(instruction, RT), 5, rt);
            convert_binaire(getRArgs(instruction, SA), 5, sa);
            rd[5] = '\0';
            rt[5] = '\0';
            sa[5] = '\0';

            if (strcmp(commande, "SLL") == 0) {
                strcpy(instruction_encodee, "00000000000");
                strcat(instruction_encodee, rt);
                strcat(instruction_encodee, rd);
                strcat(instruction_encodee, sa);
                strcat(instruction_encodee, opcode);
            } else {
                strcpy(instruction_encodee, "00000000001");
                strcat(instruction_encodee, rt);
                strcat(instruction_encodee, rd);
                strcat(instruction_encodee, sa);
                strcat(instruction_encodee, opcode);
            }
        } else if (typeR == ARG3) {
            convert_binaire(getRArgs(instruction, RD), 5, rd);
            convert_binaire(getRArgs(instruction, RT), 5, rt);
            convert_binaire(getRArgs(instruction, RS), 5, rs);
            rd[5] = '\0';
            rt[5] = '\0';
            rs[5] = '\0';

            strcpy(instruction_encodee, "000000");
            strcat(instruction_encodee, rs);
            strcat(instruction_encodee, rt);
            strcat(instruction_encodee, rd);
            strcat(instruction_encodee, "00000");
            strcat(instruction_encodee, opcode);
        } else if (typeR == ARG2) {
            convert_binaire(getRArgs(instruction, RD), 5, rs);
            convert_binaire(getRArgs(instruction, RS), 5, rt);
            rt[5] = '\0';
            rs[5] = '\0';

            strcpy(instruction_encodee, "000000");
            strcat(instruction_encodee, rs);
            strcat(instruction_encodee, rt);
            strcat(instruction_encodee, "0000000000");
            strcat(instruction_encodee, opcode);
        } else if (typeR == ARG1) {
            convert_binaire(getRArgs(instruction, RD), 5, rd);
            rd[5] = '\0';

            if (strcmp(commande, "JR") == 0) {
                strcpy(instruction_encodee, "000000");
                strcat(instruction_encodee, rd);
                strcat(instruction_encodee, "000000000000000");
                strcat(instruction_encodee, opcode);
            } else {
                strcpy(instruction_encodee, "0000000000000000");
                strcat(instruction_encodee, rd);
                strcat(instruction_encodee, "00000");
                strcat(instruction_encodee, opcode);
            }
        }


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


    // Si on veut RT, alors on prend la valeur apres le 1er #
    // Si on veut RS, alors on prend la valeur apres le 2eme #
    // Si on veut IMMEDIATE, on prend la dernière valeur

    while (instruction[i]!='\0' && tmp<0) {
        if (instruction[i]=='$' && instruction[i+2]==',') {
            //Cas ou la valeur est inférieure a 10
            res = instruction[i+1] - '0'; //Convertit instruction[i+1] en int
            tmp++;
        } else if (instruction[i]=='$' && instruction[i+2]!=',') {
            //Cas ou la valeur est supérieure a 10
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


int getJArgs(char* instruction) {

    int target=0, res=0;

    for (int i=0; instruction[i] != '\0'; i++) {
        if (instruction[i-1]==' ') {
            target = 1;
        }
        else if (target==1) {
            res += (instruction[i-1] - '0');
            res *= 10;
        }
    }
    res /= 10;

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