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

int main()
{
    FILE *fdsIn = fopen("input.txt", "r");

    // move offset
    fseek(fdsIn, 8, SEEK_CUR);
    char character;

    // use ftell to get current fp location
    printf("Move offset for string at position %ld, print: ", ftell(fdsIn));
    while ((character = fgetc(fdsIn)) != '\n')
    {
        printf("%c", character);
    }

    rewind(fdsIn);
    printf("\nRewind stream. Current position are %ld, print: ", ftell(fdsIn));
    while ((character = fgetc(fdsIn)) != '\n')
    {
        printf("%c", character);
    }

    fflush(fdsIn);
    fclose(fdsIn);
}