#include <stdio.h>
#include <stdlib.h>
#include "../headers/memoire.h"

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

//On renvoie 0 si l'adresse est trouvee, -1 sinon
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


