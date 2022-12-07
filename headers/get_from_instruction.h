#define TAILLE_MAX 100
#define NB_TYPE_I 8
#define NB_TYPE_J 2
#define NB_TYPE_R 14
#define TYPE_I 0
#define TYPE_J 1
#define TYPE_R 2
#define RT 1
#define RS 2
#define IMMEDIATE 3
#define RD 4
#define SA 5

int getType(char*);
void getOpCode(char*, char*);
int getIArgs(char*, int);
int getJArgs(char*);
int getRArgs(char*, int);
