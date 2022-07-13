/**
 * @file 09_readStringFromStream.c
 * @author makapx (https://github.com/makapx)
 * @brief read from stream with fscanf
 * @version 0.1
 * @date 2022-07-13
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    FILE *fds = fopen("input.txt", "r");
    const int BUFFSIZE = 1024;
    char buffer[BUFFSIZE];

    // read the first line
    fscanf(fds, "%127[^\n]\n", buffer);
    fprintf(stdout, "Reading: %s \n", buffer);
}