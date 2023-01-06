#include <stdio.h>
#include <stdlib.h>
#include "../headers/memoire.h"

void afficherMemoire(memoire *m) {
    if (m == NULL) {
        printf("Memoire vide\n");
    } else {
        while (m != NULL) {
            printf("data = %d, adresse = %ld\n", m->data, m->adresse);
            m = m->next;
        }
    }
}

void ajouterMemoire(memoire **m, int data, long adresse) {
    memoire *nouveau = malloc(sizeof(*nouveau));
    if (nouveau == NULL) {
        exit(EXIT_FAILURE);
    }
    nouveau->data = data;
    nouveau->adresse = adresse;
    nouveau->next = *m;
    *m = nouveau;
}

void supprimerMemoire(memoire **m, long adresse) {
    memoire *tmp = *m;
    memoire *tmp2 = NULL;
    while (tmp != NULL && tmp->adresse != adresse) {
        tmp2 = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        printf("Adresse non trouvee\n");
    } else {
        if (tmp2 == NULL) {
            *m = tmp->next;
        } else {
            tmp2->next = tmp->next;
        }
        free(tmp);
    }
}

