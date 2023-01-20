/** \file get_from_instruction.h
 *  \brief Fichier contenant les prototypes des fonctions de get_from_instruction.c 
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
