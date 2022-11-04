#define TAILLE_MAX 100
#define NB_TYPE_I 8
#define NB_TYPE_J 2
#define NB_TYPE_R 14
#define TYPE_I 0
#define TYPE_J 1
#define TYPE_R 2

void pas_a_pas();
void automatique(char*, char*, char*);
void interactif();

void convert_hexa(char*, char*);
int getType(char*);