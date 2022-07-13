/**
 * @file 08_writeStringOnStream.c
 * @author makapx (https://github.com/makapx)
 * @brief write string into stream via fprintf
 * @version 0.1
 * @date 2022-07-13
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    FILE *fds = fopen("output.txt", "a+");
    const int BUFFSIZE = 1024;
    char buffer[BUFFSIZE];

    fprintf(stdout, "Write something into file: ");
    fgets(buffer, BUFFSIZE, stdin);

    if (fprintf(fds, "%s \n", buffer) == 0)
    {
        perror("Error in writing");
        exit(1);
    }

    fprintf(stdout, "You wrote: %s", buffer);
}