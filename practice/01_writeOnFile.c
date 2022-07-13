/**
 * @file 01_writeOnFile.c
 * @author makapx (https://github.com/makapx)
 * @brief gets user input and writes into file
 * @version 0.1
 * @date 2022-07-06
 */

#include <stdio.h>    //standard input-output
#include <stdlib.h>   //standard library
#include <fcntl.h>    //file's options flag
#include <unistd.h>   //POSIX API for system calls
#include <sys/stat.h> //file's stats
#include <string.h>   //string manipulation

int main()
{
    char filename[30];
    const int BUFFSIZE = 1024;
    char buffer[BUFFSIZE];

    printf("Insert file name here: ");
    // fgets copy string + \n into filename
    fgets(filename, 30, stdin);

    // remove nl char
    size_t len = strlen(filename);
    if (len && filename[len - 1] == '\n')
    {
        filename[len - 1] = '\0';
    }
    printf("You entered: %s\n", filename);

    // creating file from scratch, R|W mode, user only
    printf("Creating your file, please wait...\n");
    int fd = creat(filename, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        perror("Error in creating file %s\n");
        exit(1);
    }

    printf("%s create with success, write something on it: \n", filename);
    fgets(buffer, BUFFSIZE, stdin);
    printf("You entered: %s", buffer);

    // write string on file
    if (write(fd, buffer, strlen(buffer)) == -1)
    {
        perror("Error in writing: ");
        exit(1);
    }
    printf("Check your file %s \n", filename);
    close(fd);
}