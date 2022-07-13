/**
 * @file 03_fileOp.c
 * @author makapx (https://github.com/makapx)
 * @brief seek and duplication of a file
 * @version 0.1
 * @date 2022-07-06
 */
#include <stdio.h>     //standard input/output
#include <stdlib.h>    //standard library
#include <unistd.h>    //POSIX API for system calls
#include <sys/fcntl.h> //file stats

int main()
{
    const int BUFFSIZE = 1024;
    char buffer[BUFFSIZE];
    long filePointer;

    // opening file in read only
    int fd = open("input.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error in opening file: ");
        exit(1);
    }

    // point to EOF
    filePointer = lseek(fd, 0L, SEEK_END);
    if (filePointer == -1)
    {
        exit(1);
    }
    printf("Pointing at %ld file location, end of file. \n", filePointer);

    // point to beginning of file
    filePointer = lseek(fd, 0L, SEEK_SET);
    if (filePointer == -1)
    {
        exit(1);
    }
    printf("Pointing at %ld file location, beginning of file. \n", filePointer);

    // point to current location
    filePointer = lseek(fd, 0L, SEEK_CUR);
    if (filePointer == -1)
    {
        exit(1);
    }
    printf("Pointing at %ld file location, current location. \n", filePointer);

    // duplicate file with dup
    printf("Coping file...\n");
    int copy = dup(fd);
    if (copy == -1)
    {
        perror("Error in coping file: ");
        exit(1);
    }
    printf("Copied with success!\n");

    close(fd);
}