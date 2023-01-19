#ifndef MEMOIRE_H
#define MEMOIRE_H

typedef struct memoire stored_memory;
struct memoire {
    int data;
    long adresse;
    stored_memory *next;
};

void printMemory(stored_memory *m);
int storeElement(stored_memory **m, int data, long adresse);
int loadElement(stored_memory **m, long, long int*);
void clearMemory(stored_memory **m);

#endif