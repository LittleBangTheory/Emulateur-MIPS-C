// Projet MIPS 2022-2023
// Auteurs: Lafage_Chognot

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

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
