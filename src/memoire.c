#include <stdio.h>
#include <stdlib.h>
#include "../headers/memoire.h"

/** \file memoire.c
 *  \brief Fichier contenant les fonctions de gestion de la mémoire.
 *  Ce fichier contient les fonctions de gestion de la mémoire, qui nous ont servi à tester le bon fonctionnement de la mémoire, ils ne sont pas appelés dans le programme final.
 */

/** \fn void printMemory(stored_memory *m)
 *  \brief Fonction d'affichage de la mémoire
 *  \param m Pointeur sur la tête de liste de la mémoire
*/
void printMemory(stored_memory *m) {
    if (m == NULL) {
        printf("Memoire vide\n");
    } else {
        while (m != NULL) {
            printf("data = %d, adresse = %ld\n", m->data, m->adresse);
            m = m->next;
        }
    }
}

/** \fn int storeElement(stored_memory **m, int data, long adresse)
 *  \brief Fonction qui stocke un élément dans la mémoire
 *  \param m Pointeur sur le pointeur sur la tête de liste de la mémoire
 *  \param data Entier contenant la donnée à stocker
 *  \param adresse Entier contenant l'adresse de la donnée
*/
int storeElement(stored_memory **m, int data, long adresse) {
    stored_memory *nouveau = malloc(sizeof(*nouveau));
    stored_memory *tmp = *m;
    if (nouveau == NULL) {
        return -1;
    }

    while(tmp != NULL && tmp->adresse != adresse) {
        tmp = tmp->next;
    }
    if (tmp != NULL) {
        tmp->data = data;
    } else {
        nouveau->data = data;
        nouveau->adresse = adresse;
        nouveau->next = *m;
        *m = nouveau;
    }
    return 0;
}


/** \fn int loadElement(stored_memory **m, long adresse, long int *resultat)
 *  \brief Fonction qui charge un élément de la mémoire
 *  \param m Pointeur sur le pointeur sur la tête de liste de la mémoire
 *  \param adresse Entier contenant l'adresse de la donnée
 *  \param resultat Pointeur sur l'entier qui contiendra le résultat de la fonction
 *  \return 0 si l'adresse est trouvée, -1 sinon
*/
int loadElement(stored_memory **m, long adresse, long int *resultat) {
    stored_memory *tmp = *m;
    while (tmp != NULL && tmp->adresse != adresse) {
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        return -1;
    } else {
        *resultat = tmp->data;
        return 0;
    }
}

/** \fn void clearMemory(stored_memory **m)
 *  \brief Fonction qui libère la mémoire
 *  \param m Pointeur sur le pointeur sur la tête de liste de la mémoire
*/
void clearMemory(stored_memory **m) {
    stored_memory *tmp = *m;
    stored_memory *tmp2 = NULL;
    while (tmp != NULL) {
        tmp2 = tmp->next;
        free(tmp);
        tmp = tmp2;
    }
    *m = NULL;
}


