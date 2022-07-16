/**
 * @file 13_link.c
 * @author makapx (https://github.com/makapx)
 * @brief
 * @version 0.1
 * @date 2022-07-15
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    struct stat fileInfo;
    stat("input.txt", &fileInfo);

    // create hard-link
    if (link("input.txt", "hard-link.txt") == -1)
    {
        perror("Error in creating hard-link");
        exit(1);
    }
    printf("Creating hard-link, inode counter: %ld \n", fileInfo.st_nlink);

    // create soft-link
    if (link("input.txt", "soft-link.txt") == -1)
    {
        perror("Error in creating soft-link");
        exit(1);
    }

    // create hard-link to soft-link
    if (link("soft-link.txt", "hard-soft-link.txt") == -1)
    {
        perror("Error in creating soft-link");
        exit(1);
    }
    printf("Creating soft-link, inode counter: %ld \n", fileInfo.st_nlink);

    unlink("hard-link.txt");
    unlink("soft-link.txt");
    unlink("hard-soft-link.txt");

    printf("Inode counter: %ld \n", fileInfo.st_nlink);
}