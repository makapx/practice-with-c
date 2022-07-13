/**
 * @file 05_readWriteFromStream.c
 * @author makapx (https://github.com/makapx)
 * @brief read and write from file stream
 * @version 0.1
 * @date 2022-07-12
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fds = fopen("input.txt", "r");
    FILE *fdsOut = fopen("output.txt", "w+");

    const int BUFF_SIZE = 1024; // buffer size
    char buffer[BUFF_SIZE];     // buffer

    int nElement = 5;     // number of element to read from file stream
    const int nbytes = 1; // dimension in byte of single element to read

    int readerElement = 0; // readed element

    do
    {
        memset(buffer, 0, BUFF_SIZE); // cleaning buffer
        readerElement = fread(buffer, nbytes, nElement, fds);
        printf("Reading: %s \n", buffer);

        // at the eof fread return less readed element then required
        if (readerElement < nElement)
        {
            nElement = readerElement;
        }
        fwrite(buffer, nbytes, nElement, fdsOut);
    } while (!feof(fds)); // end of file

    fclose(fds);
    fclose(fdsOut);
}