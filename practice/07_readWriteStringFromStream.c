/**
 * @file 07_readWriteStringFromStream.c
 * @author makapx (https://github.com/makapx)
 * @brief read/write file stream per string
 * @version 0.1
 * @date 2022-07-13
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    FILE * fdsIn = fopen("input.txt", "r");
    FILE * fdsOut = fopen("output.txt", "w+");
    const int BUFFSIZE = 1024;
    char buffer[BUFFSIZE];

    // place string in buffer. Return NULL if error
    while(fgets(buffer, BUFFSIZE, fdsIn) != NULL){
        //write string on output file
        fputs(buffer, fdsOut);
    }

    fclose(fdsIn);
    fclose(fdsOut);
}