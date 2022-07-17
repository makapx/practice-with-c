/**
 * @file 18_pipe.c
 * @author makapx (https://github.com/makapx)
 * @brief pipe
 * @version 0.1
 * @date 2022-07-17
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>

int main()
{
    int channels[2];
    int pd = pipe(channels);

    if (pd == -1)
    {
        perror("Error in creating pipe");
        exit(1);
    }

    if (fork() != 0)
    {
        close(1);           // close standard output
        dup(channels[1]);   // redirect standard output to pipe
        close(channels[0]); // closing input channel

        execlp("ls", "ls", NULL);
        perror("Execl 1 error");
        exit(1);
    }
    else
    {
        close(0);           // close standard input
        dup(channels[0]);   // redirect standard input to pipe
        close(channels[1]); // close output channel
        execlp("grep", "grep", "pipe", NULL);
        perror("Execl 2 error");
        exit(1);
    }
}
