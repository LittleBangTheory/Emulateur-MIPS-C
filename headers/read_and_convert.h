/** \file read_and_convert.h
 *  \brief Fichier contenant les prototypes des fonctions de read_and_convert.c
*/

/** \def TAILLE_MAX
 *  \brief Définition de la taille maximale d'une instruction
 *  \def NB_TYPE_I
 *  \brief Définition du nombre de types d'instructions I
 *  \def NB_TYPE_J
 *  \brief Définition du nombre de types d'instructions J
 *  \def NB_TYPE_R
 *  \brief Définition du nombre de types d'instructions R
 *  \def TYPE_I
 *  \brief Définition du numéro de type d'instruction I
 *  \def TYPE_J
 *  \brief Définition du numéro de type d'instruction J
 *  \def TYPE_R
 *  \brief Définition du numéro de type d'instruction R
 *  \def RT
 *  \brief Définition de l'argument RT
 *  \def RS
 *  \brief Définition de l'argument RS
 *  \def IMMEDIATE
 *  \brief Définition de l'argument IMMEDIATE
 *  \def RD
 *  \brief Définition de l'argument RD
 *  \def SA
 *  \brief Définition de l'argument SA
*/
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
int getType(char*);
int binaryToInt(char*);