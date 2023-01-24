// Projet MIPS 2022-2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/main.h"

/** \file main.c
 *  \brief Fichier contenant le main du projet
 *  \author Chognot et Lafage
*/

/** \fn int main(int argc, char **argv)
 *  \brief Fonction principale du projet
 *  \param argc Nombre d'arguments passés au programme
 *  La fonction appelle la fonction interactif si aucun argument n'est passé au programme. Elle appelle la fonction pas_a_pas si un argument est passé au programme. Elle appelle la fonction automatique si deux arguments sont passés au programme.
*/
int main(int argc, char **argv)
{
   if (argc==1) {
      interactif();
   } 
   else if (argc==3) {
      pas_a_pas(argv[1]);
   }
   else if (argc==4) {
      automatique(argv[1], argv[2], argv[3]);
   }
    return 0;
}