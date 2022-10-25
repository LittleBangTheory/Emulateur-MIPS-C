#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void convert_hexa(char* instruction, char* instruction_hexa) {

    int j=0;
    for (int i=0; instruction[i] != '\n'; i++) {
        sprintf((char*)(instruction_hexa+j), "%02X", instruction[i]);
        j+=2;
    }
}