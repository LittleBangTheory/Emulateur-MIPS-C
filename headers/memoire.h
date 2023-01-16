#ifndef MEMOIRE_H
#define MEMOIRE_H

typedef struct memoire memoire;
struct memoire {
    int data;
    long adresse;
    memoire *next;
};

void printMemory(memoire *m);
int storeElement(memoire **m, int data, long adresse);
int loadElement(memoire **m, long, int*);
void clearMemory(memoire **m);

#endif