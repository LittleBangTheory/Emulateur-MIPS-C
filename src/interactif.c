#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/interactif.h"
#include "../headers/read_and_convert.h"
#include "../headers/execute.h"

/** \file interactif.c
 *  \brief Fichier executant le mode interactif
 */

/** \fn void interactif
 *  \brief Fonction executant le mode interactif
 *  \param file_programme Le fichier contenant le programme à executer
 *  La fonction initialise les registres, la mémoire et la liste des instructions.
 *  Elle lit ensuite l'instruction entrée par l'utilisateur dans l'invite de commande, et les ajoute à la liste des instructions.
 *  On aurait pu se passer de la liste des instructions car il n'y a pas de fonctions de type branch et jump dans le mode interactif. 
 *  Elle execute ensuite l'instruction, et affiche les registres.
 */
void interactif() {
    printf("Mode interactif\n");

    //Instructions rentrées par l'utilisateur
    char instruction[TAILLE_MAX];
    char instruction_hexa[TAILLE_MAX];
    int scanf_return;
    char* instruction_clean;

    //Initialisation listes chainées mémoire et instructions
    stored_memory* memoire = NULL;
    stored_instruction* liste_instruction = NULL;
    char* commande = malloc(sizeof(char)*6); 
    int arg1, arg2, arg3, line_number=0;
    stored_instruction* current = NULL;

    //Initialisation registres
    long int registre[NB_REGISTRE];
    define_registers(registre);

    printf("Entrez une instruction: ");
    scanf_return = scanf(" %[^\n]", instruction);
    while(strcmp(instruction, "EXIT")){
        //Lecture de l'instruction
        if (scanf_return == EOF) {
            printf("Erreur de lecture de l'instruction");
            exit(EXIT_FAILURE);
        }

        //On enlève les commentaires
        instruction_clean = strtok(instruction, "#");

        //conversion en hexa
        convert_hexa(instruction_clean, instruction_hexa);
        printf("%s\n", instruction_hexa);

        //Ajout de l'instruction dans la liste chainée
        if (instruction[0] >= 65 && instruction[0] <= 90) {
            get_args(instruction_clean, &commande, &arg1, &arg2, &arg3);
            add_instruction(commande, arg1, arg2, arg3, line_number, &liste_instruction);
            line_number++;
        }

        //initialisation de current
        if (current == NULL) {
            current = liste_instruction;
        }

        //Execution de l'instruction
        if (current->next != NULL) {
            current = current->next;
        }        
        execute(&current, registre, &memoire, stdout);
        
        //Affichage des registres
        //afficherRegistres(registre, stdout);

        //Lecture de la prochaine instruction
        printf("Entrez une instruction: ");
        scanf_return = scanf(" %[^\n]", instruction);
    }

    //Libération de la mémoire
    free(commande);
    clear_instructions(&liste_instruction);
    clearMemory(&memoire);
}