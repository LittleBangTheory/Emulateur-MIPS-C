typedef struct memoire memoire;
struct memoire {
    int data;
    long adresse;
    memoire *next;
};

void afficherMemoire(memoire *m);
void ajouterMemoire(memoire **m, int data, long adresse);
void supprimerMemoire(memoire **m, long adresse);