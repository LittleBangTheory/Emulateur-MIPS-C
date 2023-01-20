#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/pas_a_pas.h"
#include "../headers/read_and_convert.h"
#include "../headers/save_instruction.h"
#include "../headers/get_from_instruction.h"
#include "../headers/execute.h"

/** \file pas_a_pas.c
 *  \brief Fichier executant le mode pas à pas
 */

/** \fn void pas_a_pas(char* file_programme)
 *  \brief Fonction executant le mode pas à pas
 *  \param file_programme Le fichier contenant le programme à executer
 *  La fonction initialise les registres, la mémoire et la liste des instructions, puis ouvre le fichier contenant le programme à executer. 
 *  Elle lit ensuite le fichier ligne par ligne, convertit les instructions en hexadécimal, et les ajoute à la liste des instructions. 
 *  Enfin, elle execute le programme en parcourant la liste chainée, en modifiant les registres et la mémoire, et en affichant l'instruction et l'état des registres à chaque étape.
 *  Elle demande que l'utilisateur appuie sur entrée pour passer à l'étape suivante.
 *  La fonction pour convertir en héxadécimal a été implémentée avant la création de la liste chainée contenant les instructions, elle n'est donc pas complatible avec ce nouveau mode d'exécution. C'est pourquoi les instructions en hexadécimal sont affichées avant l'execution. Nous ne l'avons pas modifié car nous ne sommes pas évalués la dessus pour ce rendu.
 */
 
void pas_a_pas(char* file_programme) {
    char instruction[TAILLE_MAX];
    char instruction_hexa[TAILLE_MAX];
    char enter;

    FILE* programme;

    programme = fopen(file_programme, "r");

    if (programme==NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(EXIT_FAILURE);
    } 

    //Initialisation de la mémoire et de la liste des instructions
    stored_memory* memoire = NULL;
    stored_instruction* liste_instruction = NULL;

    char* commande = malloc(sizeof(char)*5);
    int arg1, arg2, arg3, line_number=0;
    
    //Initialisation des registres
    long int registre[NB_REGISTRE];
    define_registers(registre);

    char* instruction_clean;

    //Lecture du fichier, convertion et ajout des instructions dans la liste chainée
    while (fgets(instruction, TAILLE_MAX, programme) != NULL) {
        if (instruction[0] >= 65 && instruction[0] <= 90) {
            //On enlève les commentaires
            instruction_clean = strtok(instruction, "#");
            //printf("Instruction rentrée : %s\n", instruction);
            convert_hexa(instruction_clean, instruction_hexa);
            printf("%s\n", instruction_hexa);

            get_args(instruction_clean, &commande, &arg1, &arg2, &arg3);
            add_instruction(commande, arg1, arg2, arg3, line_number, &liste_instruction);
            line_number++;
        }
    }

    //Execution du programme
    stored_instruction* current = liste_instruction;
    while (current != NULL){
        //afficher_instruction_courrante(current, stdout);
        execute(&current, registre, &memoire, stdout);

        printf("Press enter to continue\n");
        enter = scanf("%c", &enter);

        current = current->next;
    }



    free(commande);
    clear_instructions(&liste_instruction);
    clearMemory(&memoire);
    fclose(programme);
}