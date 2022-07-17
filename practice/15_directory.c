/**
 * @file 15_directory.c
 * @author makapx (https://github.com/makapx)
 * @brief work with directory
 * @version 0.1
 * @date 2022-07-17
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h> //for directory

int main()
{
    DIR *currentDir = opendir("."); // stream directory
    if (currentDir == NULL)
    {
        perror("Error in open current directory\n");
        exit(1);
    }

    struct dirent *dirStat = readdir(currentDir); // struct dir
    if (dirStat == NULL)
    {
        perror("Error in reading current directory\n");
        exit(1);
    }

    printf("Dirname: %s\n", dirStat->d_name); // dirname (POSIX COMPATIBLE)
    printf("Dirtype: %d\n", dirStat->d_type); // type   (NON POSIX STANDARD)

    // the same as would be returned by calling telldir(3)
    // at the current position in the directory stream
    printf("Current position: %ld\n", dirStat->d_off); // (NON POSIX STANDARD)
    printf("Current position with telldir: %ld\n", telldir(currentDir));

    printf("Record len: %d\n", dirStat->d_reclen); // record len (NON POSIX STANDARD)
    printf("inumber: %ld\n", dirStat->d_ino);      // inode number (POSIX COMPATIBLE)

    closedir(currentDir);
}
