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


void define_registers(long int* registre) {
    //on aurait pu créer une variable de type constant int pour le $0, mais par simplicité on utilisera directement registre[0]
    for (int i=0; i<NB_REGISTRE; i++) {
        //on initialise tous les registres à 0, pour savoir à la fin de l'exécution si un registre a été modifié
        registre[i]=0;
    }
}

void get_args(char* instruction, char** commande, int* arg1, int* arg2, int* arg3) {
    int args[3];
    int i = 0;

    const char* separators = " ,()$\n";
    char* token = strtok(instruction, separators);
    while (token != NULL) {
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

    //pour savoir si un argument a été modifié
    for (int i=0; i<3; i++) {
        args[i] = -32768;
    }
}

void execute(stored_instruction* instruction, long int* registre, stored_memory** memoire) {
    char* command = malloc(sizeof(instruction->command));
    strcpy(command, instruction->command);
    int arg1 = instruction->arg1;
    int arg2 = instruction->arg2;
    int arg3 = instruction->arg3;
    //disjonction de cas pour toutes les instructions
    if (strcmp(command, "ADD") == 0) {
        registre[arg1] = registre[arg2] + registre[arg3];
    } else if (strcmp(command, "ADDI") == 0) {
        registre[arg1] = registre[arg2] + arg3;
    } else if (strcmp(command, "AND") == 0) {
        registre[arg1] = registre[arg2] & registre[arg3];
    }
    //Branch 
    else if (strcmp(command, "BEQ") == 0) {
        if (registre[arg1] == registre[arg2] && arg3 != 0) {
            branch(instruction, arg3, registre, *memoire);
        }
    } else if (strcmp(command, "BLEZ") == 0) {
        if (registre[arg1] <= 0 && arg2 != 0) {
            branch(instruction, arg2, registre, *memoire);
    }
    } else if (strcmp(command, "BGTZ") == 0) {
        if (registre[arg1] > 0 && arg2 != 0) {
            branch(instruction, arg2, registre, *memoire);
        }
    } else if (strcmp(command, "BNE") == 0) {
        if (registre[arg1] != registre[arg2] && arg3 != 0) {
            branch(instruction, arg3, registre, *memoire);
        }
    } 
    //Div
    else if(strcmp(command, "DIV") == 0){
        registre[HI]=registre[arg1]/registre[arg2];
        registre[LO]=registre[arg1]%registre[arg2];
    }
    //Jump
    else if(strcmp(command, "J") == 0){
        instruction = instruction->next;
        execute(instruction, registre, memoire);
        jump(instruction, arg1);
    } else if(strcmp(command, "JAL") == 0){
        registre[31] = instruction->line_number;
        instruction = instruction->next;
        execute(instruction, registre, memoire);
        jump(instruction, arg1);
        execute(instruction, registre, memoire);
        jump(instruction, registre[31]);
    } else if(strcmp(command, "JR") == 0){
        instruction = instruction->next;
        execute(instruction, registre, memoire);
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
        registre[HI] = ((registre[arg1] * registre[arg2]) & 18446744069414584320) >> 32; 
        //18446744069414584320 est 1 [63;32] puis 0 sur [31;0] en hexa
        registre[LO] = ((registre[arg1] * registre[arg2]) & 4294967295);
        //4294967295 est 0 [63;32] puis 1 sur [31;0] en hexa
    } 
    //Or
    else if(strcmp(command, "OR") == 0){
        registre[arg1] = registre[arg2] | registre[arg3];
    } 
    //Rotate
    else if(strcmp(command, "ROTR") == 0){
        registre[arg1] = (registre[arg2] >> arg3) | (registre[arg2] << (32 - arg3));
    }
    //Shift 
    else if(strcmp(command, "SLL") == 0){
        registre[arg1] = registre[arg2] << arg3;    
    } else if(strcmp(command, "SLT") == 0){
        if (registre[arg2] < registre[arg3]) {
            registre[arg1] = 1;
        } else {
            registre[arg1] = 0;
        }
    } else if(strcmp(command, "SRL") == 0){
        registre[arg1] = registre[arg2] >> arg3;
    } 
    //Sub
    else if(strcmp(command, "SUB") == 0){
        registre[arg1] = registre[arg2] - registre[arg3];
    } 
    //Store
    else if(strcmp(command, "SW") == 0){
        storeElement(memoire, registre[arg1], registre[arg3] + arg2);
        //printMemory(memoire);
    } 
    //Exclusive OR
    else if(strcmp(command, "XOR") == 0){
        registre[arg1] = registre[arg2] ^ registre[arg3];
    } else {
        printf("Erreur : commande inconnue\n");
    }
}

void afficherRegistres(long int* registre) {
    for (int i=0; i<NB_REGISTRE-2; i++) {
        if (registre[i] != 0) {
            printf("$%d:%ld\n", i, registre[i]);
        }
    }
    printf("HI:%ld\n", registre[HI]);
    printf("LO:%ld\n", registre[LO]);
}
