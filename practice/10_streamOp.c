/**
 * @file 10_streamOp.c
 * @author makapx (https://github.com/makapx)
 * @brief stream operations
 * @version 0.1
 * @date 2022-07-14
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    FILE * fdsIn = fopen("input.txt", "r");
    fprintf(stdout, "%d\n", fseek(fdsIn, 2, SEEK_CUR));
}