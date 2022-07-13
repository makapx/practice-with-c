/**
 * @file 06_readWriteBytesFromStream.c
 * @author makapx (https://github.com/makapx)
 * @brief read/write from file stream per bype
 * @version 0.1
 * @date 2022-07-13
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    FILE *fdsIn = fopen("input.txt", "r");
    FILE *fdsOut = fopen("output.txt", "w+");
    const int BUFFSIZE = 1024;
    char buffer[BUFFSIZE];
    int readed;
    int writed;

    while (!feof(fdsIn))
    {
        readed = fgetc(fdsIn);
        if (readed != -1)
        {
            writed = fputc(readed, fdsOut);
            if (writed == -1 /* (!= EOF) */)
            {
                perror("Error in writing file");
                exit(1);
            }
        }
    }
    fclose(fdsIn);
    fclose(fdsOut);
}