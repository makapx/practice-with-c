/**
 * @file 14_mappedFile.c
 * @author makapx (https://github.com/makapx)
 * @brief memory-mapped file
 * @version 0.1
 * @date 2022-07-16
 */
#define _GNU_SOURCE // linux only
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/stat.h>

int main()
{
    int fdIn = open("input.txt", O_RDONLY);
    int fdOut = open("output.txt", O_RDWR | O_TRUNC);

    struct stat fdStat;
    stat("input.txt", &fdStat);
    const int MAPSIZE = fdStat.st_size;

    char *mappedIn = (char *)mmap(NULL, MAPSIZE, PROT_READ, MAP_PRIVATE, fdIn, 0);
    if (mappedIn == MAP_FAILED)
    {
        perror("Error in create input map");
        exit(1);
    }

    // truncate file !important if file size is less then chosen size
    if (ftruncate(fdOut, fdStat.st_size) == -1)
    {
        perror("Error on truncate");
        exit(1);
    }

    // use map shared for output file
    char *mappedOut = (char *)mmap(NULL, MAPSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fdOut, 0);
    if (mappedOut == MAP_FAILED)
    {
        perror("Error in create output map");
        exit(1);
    }

    // write on mapped file
    for (int i = 0; i < MAPSIZE; i++)
    {
        mappedOut[i] = mappedIn[i];
    }

    // write on file
    msync(mappedOut, MAPSIZE, MS_SYNC);

    // linux only
    // mremap(addr, MAPSIZE, MAPSIZE + 2, MREMAP_MAYMOVE);

    close(fdIn);
    close(fdOut);
    munmap(mappedOut, MAPSIZE);
    munmap(mappedIn, MAPSIZE);
}