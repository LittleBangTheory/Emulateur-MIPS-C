#include <stdio.h>
#include <stdlib.h>
#include "../headers/automatique.h"
#include "../headers/read_and_convert.h"
#include "../headers/memoire.h"
#include "../headers/save_instruction.h"
#include "../headers/execute.h"

void automatique(char* file_programme, char* file_sortie_assemblage, char* file_sortie_execution) {

    char instruction[TAILLE_MAX];
    char instruction_hexa[TAILLE_MAX];

    FILE* programme;
    FILE* sortie_assemblage;
    FILE* sortie_execution;

    programme = fopen(file_programme, "r");
    sortie_assemblage = fopen(file_sortie_assemblage, "w");
    sortie_execution = fopen(file_sortie_execution, "w");
    if (programme==NULL || sortie_assemblage==NULL || sortie_execution==NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(EXIT_FAILURE);
    }

    //Initialisation de la mémoire et de la liste des instructions
    stored_memory* memoire = NULL;
    stored_instruction* liste_instruction = NULL;

    //Initialisation des registres
    long int registre[NB_REGISTRE];
    define_registers(registre);


    char* commande = malloc(sizeof(char)*5);
    int arg1, arg2, arg3, line_number=0;
    
    //Lecture du fichier, conversion et écriture dans le fichier de sortie, ajout des instructions dans la liste
    while (fgets(instruction, TAILLE_MAX, programme) != NULL) {
        if (instruction[0] >= 65 && instruction[0] <= 90) {
            convert_hexa(instruction, instruction_hexa);
            fprintf(sortie_assemblage, "%s\n", instruction_hexa);

            get_args(instruction, &commande, &arg1, &arg2, &arg3);
            add_instruction(commande, arg1, arg2, arg3, line_number, &liste_instruction);
            line_number++;
        }
    }

    //Execution du programme
    stored_instruction* current = liste_instruction;
    while (current != NULL){
        execute(current, registre, &memoire);
        current = current->next;
    }

    afficherRegistres(registre, stdout);
    

    fclose(programme);
    fclose(sortie_assemblage);
    fclose(sortie_execution);
    free(commande);
    clear_instructions(&liste_instruction);
    clearMemory(&memoire);
}