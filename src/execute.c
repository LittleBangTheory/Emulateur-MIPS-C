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


void define_registers(int* registre) {
    //on aurait pu créer une variable de type constant int pour le $0, mais par simplicité on utilisera directement registre[0]
    registre[0]=0;
    for (long int i=1; i<NB_REGISTRE; i++) {
        //on initialise tous les registres à la valeur max du type long int, pour savoir à la fin de l'exécution si un registre a été modifié
        registre[i]=2147483647;
    }
}

void fill_instructions(char* instruction, struct instruction** liste_instruction) {
    int args[2];
    int i = 0;
    char commande[10];

    const char* separators = " ,()$";
    char* token = strtok(instruction, separators);
    while (token != NULL) {
        printf("%s\n", token);
        if (i == 0) {
            //on récupère la commande
            char* commande = token;
        } else {
            //on récupère les opérandes
            args[i-1] = atoi(token);
        }
        token = strtok(NULL, separators);
    }

    add_instruction(commande, args[0], args[1], args[2], liste_instruction);
}

void execute(char* command, int* arg1, int* arg2, int* arg3, int* registre, memoire** memoire) {
    //disjonction de cas pour toutes les instructions
    if (strcmp(command, "ADD") == 0) {
        registre[*arg1] = registre[*arg2] + registre[*arg3];
    } else if (strcmp(command, "ADDI") == 0) {
        registre[*arg1] = registre[*arg2] + *arg3;
    } else if (strcmp(command, "AND") == 0) {
        registre[*arg1] = registre[*arg2] & registre[*arg3];
    } else if (strcmp(command, "BEQ") == 0) {
        if (registre[*arg1] == registre[*arg2]) {
            //on saute à l'instruction cible
        }
    } else if (strcmp(command, "BLEZ") == 0) {
        if (registre[*arg1] <= 0) {
            //on saute à l'instruction cible
    }
    } else if (strcmp(command, "BGTZ") == 0) {
        if (registre[*arg1] > 0) {
            //on saute à l'instruction cible
        }
    } else if (strcmp(command, "BNE") == 0) {
        /*
        if () {
            //on saute à l'instruction cible
        }
        */
    } else if(strcmp(command, "DIV") == 0){
        registre[LO]=registre[*arg1]/registre[*arg2];
        registre[HI]=registre[*arg2]%registre[*arg2];
    } else if(strcmp(command, "J") == 0){
        
    } else if(strcmp(command, "JAL") == 0){
        
    } else if(strcmp(command, "JR") == 0){
        
    } else if(strcmp(command, "LUI") == 0){
        registre[*arg1] = *arg3 << 16;
    } else if(strcmp(command, "LW") == 0){
        
    } else if(strcmp(command, "MFHI") == 0){
        registre[*arg1] = registre[HI];
    } else if(strcmp(command, "MFLO") == 0){
        registre[*arg1] = registre[LO];
    } else if(strcmp(command, "MULT") == 0){
        registre[LO] = registre[*arg1] * registre[*arg2];
    } else if(strcmp(command, "OR") == 0){
        registre[*arg1] = registre[*arg2] | registre[*arg3];
    } else if(strcmp(command, "ROTR") == 0){
    
    } else if(strcmp(command, "SLL") == 0){
        registre[*arg1] = registre[*arg2] << *arg3;    
    } else if(strcmp(command, "SLT") == 0){
        if (registre[*arg2] < registre[*arg3]) {
            registre[*arg1] = 1;
        } else {
            registre[*arg1] = 0;
        }
    } else if(strcmp(command, "SRL") == 0){
        registre[*arg1] = registre[*arg2] >> *arg3;
    } else if(strcmp(command, "SUB") == 0){
        registre[*arg1] = registre[*arg2] - registre[*arg3];
    } else if(strcmp(command, "SW") == 0){
        storeElement(memoire, registre[*arg1], registre[*arg2] + *arg3);
        printMemory(*memoire);
    } else if(strcmp(command, "XOR") == 0){
        registre[*arg1] = registre[*arg2] ^ registre[*arg3];
    } else {
        printf("Erreur : commande inconnue\n");
    }
}
