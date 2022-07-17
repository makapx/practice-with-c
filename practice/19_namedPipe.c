/**
 * @file 19_namedPipe.c
 * @author makapx (https://github.com/makapx)
 * @brief named pipe / FIFO queue
 * @version 0.1
 * @date 2022-07-17
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    int npd = mkfifo("npQueue", 0660);
    if (npd == -1)
    {
        perror("Error in creating named pipe");
        exit(1);
    }

    if (fork() != 0)
    { // enqueue
        write(npd, "Hello from mother\n", sizeof(char) * 19);
    }
    else
    {
        char buffer[19];
        read(npd, buffer, 20); // dequeue
        unlink("npQueue");     // unlink queue
    }
}