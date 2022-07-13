/**
 * @file 02_readFromFile.c
 * @author makapx (https://github.com/makapx)
 * @brief reads from a file
 * @version 0.1
 * @date 2022-07-06
 */

#include <stdio.h>     //standard input/output
#include <stdlib.h>    //standard library
#include <unistd.h>    //POSIX API for system calls
#include <sys/fcntl.h> //file stats
#include <string.h>    //string

int main()
{
    const int BUFFSIZE = 1024;
    char buffer[BUFFSIZE];

    // open file in R|W mode, create if not exist
    int fd = open("my-file", O_RDWR | O_TRUNC | O_CREAT, 0660);
    printf("Write something: ");
    fgets(buffer, BUFFSIZE, stdin);
    write(fd, buffer, strlen(buffer));

    // read from file
    if (read(fd, buffer, BUFFSIZE) == -1)
    {
        perror("Error in read file");
        exit(1);
    }

    // insert end of line
    size_t len = strlen(buffer);
    if (len)
    {
        buffer[len] = '\0';
    }

    printf("Read from file: %s\n", buffer);
    close(fd);
}