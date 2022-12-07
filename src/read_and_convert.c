#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "../headers/read_and_convert.h"
#include "../headers/get_from_instruction.h"

void clear_instruction(char* instruction, char** adresse, int* size) {
    //taille de la chaine
    *size=strlen(instruction);
    //on enlève les espaces et les retours à la ligne
    int i=(*size)-1;
    while (instruction[i]=='\n' || instruction[i]=='\r' || instruction[i]==' ') {
        i--;
    } 
    //on alloue la mémoire pour la chaine nettoyée
    char* instruction_clean=malloc((i+2)*sizeof(char));
    //on vérifie que la mémoire a bien été allouée
    if (instruction_clean==NULL) {
        printf("Erreur d'allocation mémoire");
        exit(1);
    }
    //on copie la chaine nettoyée
    for (int j=0; j<=i; j++) {
        instruction_clean[j]=instruction[j];
    }
    instruction_clean[i+1]='\0';
    *adresse = instruction_clean;
}

void convert_hexa(char* instruction, char* instruction_hexa) {
    //Initialisation des variables
    int dec_val=0, taille_instruction_encodee, size_of_instruction_clean;
    char instruction_encodee[32*sizeof(char)]; //Plus grande taille si ca marche pas
    char* adress_of_instruction_clean;

    //Nettoyer la chaine
    clear_instruction(instruction, &adress_of_instruction_clean, &size_of_instruction_clean);
    char* instruction_clean = adress_of_instruction_clean;
    //Encoder la chaine
    encoder(instruction_clean, instruction_encodee);

    //Trouver la taille de la chaine
    taille_instruction_encodee = strlen(instruction_encodee);
    
    //Convertir le binaire en hexa
    for (int j=taille_instruction_encodee-1; j>=0; j--) {
        dec_val += (instruction_encodee[j] - '0')*pow(2, taille_instruction_encodee-j-1);
    }
    sprintf(instruction_hexa, "%.8x\n", dec_val);
    
    //Libérer la mémoire de instruction_clean
    free(instruction_clean);
}

void convert_binaire(int valeur, int nb_bits, char* valeur_binaire) {

    int binaryNum[32];
    int i=0, k=0, negatif=0, invert=0;
    int nb_zeros=0;

    //Si la valeur est negative, on change son signe et on met la variable negatif a 1
    if (valeur<0) {
        negatif = 1;
        valeur *= -1;
    }
   
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

    //Si la valeur est negative, on le code en complément a 2
    if (negatif==1) {
        for (int j=strlen(valeur_binaire)-1; j>=0; j--) {
            if (valeur_binaire[j] == '0' && invert == 1) {
                valeur_binaire[j] = '1';
            } else if (valeur_binaire[j] == '1' && invert == 1) {
                valeur_binaire[j] = '0';
            }

            if (valeur_binaire[j] == '1') {
                invert = 1;
            }
        }
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