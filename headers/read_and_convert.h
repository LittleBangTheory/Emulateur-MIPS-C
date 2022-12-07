#define TAILLE_MAX 100
#define NB_TYPE_R_SA 3
#define NB_TYPE_R_ARG1 3
#define NB_TYPE_R_ARG2 2
#define NB_TYPE_R_ARG3 6
#define ARG1 0
#define ARG2 1
#define ARG3 2
#define ARGSA 3
#define TYPE_I 0
#define TYPE_J 1
#define TYPE_R 2
#define RT 1
#define RS 2
#define IMMEDIATE 3
#define RD 4
#define SA 5

void clear_instruction(char*, char**, int*);
void convert_hexa(char*, char*);
void convert_binaire(int, int, char*);
void encoder(char*, char*);