/**
 * @file 04_fileStream.c
 * @author makapx (https://github.com/makapx)
 * @brief work with stream
 * @version 0.1
 * @date 2022-07-07
 */

#include <stdio.h>     //standard I/O
#include <stdlib.h>    //standard library
#include <unistd.h>    //POSIX API
#include <sys/fcntl.h> //file consts

int main()
{

    // Open stream in r/w mode, truncate if already exist
    FILE *streamWP = fopen("input.txt", "w+");
    if (streamWP == NULL)
    {
        perror("File not exist \n");
    }

    // Open stream in r only mode
    FILE *streamRO = fopen("input.txt", "r");
    if (streamRO == NULL)
    {
        perror("File not exist \n");
    }

    // Open stream with existing fd via fdopen
    int fd = open("input.txt", O_RDONLY);
    FILE *streamFromFd = fdopen(fd, "r");

    // Close streams
    fclose(streamFromFd);
    fclose(streamRO);
    fclose(streamWP);
    close(fd);
}