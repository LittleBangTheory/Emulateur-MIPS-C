#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/save_instruction.h"
#include "../headers/memoire.h"
#include "../headers/execute.h"


/** \file save_instruction.c
 *  \brief Fichier contenant les fonctions de sauvegarde des instructions 
*/

/** \fn void add_instruction(char* command, int arg1, int arg2, int arg3, int line_number, stored_instruction **current)
 *  \brief Fonction qui ajoute une instruction à la liste chainée
 *  \param command Chaine de caractère contenant la commande
 *  \param arg1 Entier contenant le premier argument
 *  \param arg2 Entier contenant le deuxième argument
 *  \param arg3 Entier contenant le troisième argument
 *  \param line_number Entier contenant le numéro de ligne de la nouvelle instruction
 *  \param current Pointeur sur le pointeur sur la tête de liste de la liste chainée
 *  La fonction alloue de la mémoire pour une nouvelle instruction. Si la liste est vide, elle devient la tête de liste. Sinon, elle est ajoutée à la fin de la liste.
*/
void add_instruction(char* command, int arg1, int arg2, int arg3, int line_number, stored_instruction **current){

    stored_instruction* suivant = *current;
    stored_instruction* new_instruction = malloc(sizeof(stored_instruction));

    if (new_instruction == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    if (suivant == NULL) {
        *current = new_instruction;
        strcpy(new_instruction->command, command);
        new_instruction->arg1 = arg1;
        new_instruction->arg2 = arg2;
        new_instruction->arg3 = arg3;
        new_instruction->line_number = line_number;
        new_instruction->next = NULL;
        new_instruction->prev = NULL;
    } else {
        while (suivant->next != NULL) {
            suivant = suivant->next;
        }

        suivant->next = new_instruction;
        strcpy(new_instruction->command, command);
        new_instruction->arg1 = arg1;
        new_instruction->arg2 = arg2;
        new_instruction->arg3 = arg3;
        new_instruction->line_number = line_number;
        new_instruction->next = NULL;
        new_instruction->prev = suivant;
    }
}

/** \fn void afficher_instructions(stored_instruction* last_instruction)
 *  \brief Fonction qui affiche les instructions de la liste chainée
 *  \param last_instruction Pointeur sur la queue de liste de la liste chainée
*/
void afficher_instructions(stored_instruction* last_instruction){
    stored_instruction* current = last_instruction;
    if (current == NULL){
        printf("No instruction to display\n");
    }
    while (current != NULL){
        printf("Stored_instruction :%s %d %d %d\n", current->command, current->arg1, current->arg2, current->arg3);
        current = current->next;
    }
}

/** \fn void afficher_instruction_courrante(stored_instruction* current, FILE* sortie)
 *  \brief Fonction qui affiche l'instruction courante de la liste chainée, utilisée pour l'affichage dans le fichier de sortie et dans le terminal
 *  \param current Pointeur sur l'instruction courante de la liste chainée
 *  \param sortie Pointeur sur le fichier de sortie
*/
void afficher_instruction_courrante(stored_instruction* current, FILE* sortie) {
    if (sortie != NULL) {
        fprintf(sortie, "%s %d %d %d\n", current->command, current->arg1, current->arg2, current->arg3);
    }
}

/** \fn void clear_instructions(stored_instruction **instruction)
 *  \brief Fonction qui libère toute la mémoire allouée pour la liste chainée
 *  \param instruction Pointeur sur le pointeur sur la tête de liste de la liste chainée
*/
void clear_instructions(stored_instruction **instruction) {
    stored_instruction *tmp = *instruction;
    stored_instruction *tmp2 = NULL;
    while (tmp != NULL) {
        tmp2 = tmp->next;
        free(tmp);
        tmp = tmp2;
    }
    *instruction = NULL;
}

/** \fn void branch(stored_instruction** current, int branch_value)
 *  \brief Fonction qui permet de sauter à une instruction précise de la liste chainée
 *  \param current Pointeur sur le pointeur sur l'instruction courante de la liste chainée
 *  \param branch_value Entier contenant le numéro de l'instruction à laquelle on veut sauter
 *  La fonction accepte toutes les valeurs de saut, sauf 1. Si cette condition est remplie, la fonction saute à l'instruction numéro branch_value.
 *  Si le branch est de 1, il ne se passe rien. 
 *  Le branch de 0 est géré directement dans l'appel de la fonction, dans execute.c
 *  Si le branch est supérieur au nombre d'instructions, le programme s'arrête.
*/
void branch(stored_instruction** current, int branch_value){
    int i = 0;
    if (branch_value < 0){  
        while (i > branch_value && (*current)->prev != NULL){
            (*current) = (*current)->prev;
            i--;
            if ((*current)->prev == NULL){
                printf("Error : branch value is too low\n");
                exit(EXIT_FAILURE);
            }
        }
    } else if (branch_value > 1) {
        while(i < branch_value-1 && (*current)->next != NULL){
            (*current) = (*current)->next;
            i++;
            if ((*current)->next == NULL){
                printf("Error : branch value is too high\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

/** \fn void jump(stored_instruction** current, int line_number)
 *  \brief Fonction qui permet de sauter à une instruction précise de la liste chainée
 *  \param current Pointeur sur le pointeur sur l'instruction courante de la liste chainée
 *  \param line_number Entier contenant le numéro de l'instruction à laquelle on veut sauter
 *  La fonction compare le numéro de ligne auquel on veut sauter et le numéro de ligne de l'instruction courante, et se déplace en fonction.
 *  Si le saut est supérieur au nombre d'instructions, le programme s'arrête.
*/
void jump(stored_instruction** current, int line_number){
    if (line_number > ((*current)->line_number)+1){ 
        while (line_number > ((*current)->line_number)+1 && (*current)->next != NULL){
            printf("Instruction courante : %s\n", (*current)->command);
            (*current) = (*current)->next;
            if ((*current)->next == NULL){
                printf("Error : jump value is too high\n");
                exit(EXIT_FAILURE);
            }
        }
    } else if (line_number < ((*current)->line_number)-1){
        while(line_number < ((*current)->line_number)-1 && (*current)->prev != NULL){
            printf("Instruction courante : %s\n", (*current)->command);
            (*current) = (*current)->prev;
            if ((*current)->prev == NULL){
                printf("Error : jump value is too low\n");
                exit(EXIT_FAILURE);
            }
        }
    } else if (line_number == ((*current)->line_number)-1){
        (*current) = (*current)->prev;
    } else if (line_number == ((*current)->line_number)+1){
        (*current) = (*current)->next;
    }
    printf("Jump complete\n");
}
