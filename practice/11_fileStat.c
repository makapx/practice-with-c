/**
 * @file 11_fileStat.c
 * @author makapx (https://github.com/makapx)
 * @brief use stat call to get file info
 * @version 0.1
 * @date 2022-07-14
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    // init stat struct for file info
    struct stat fileStat;
    stat("input.txt", &fileStat);

    //create sym link
    struct stat fileSymStat;
    struct stat linkStat;
    symlink("input.txt", "symInput.txt");
    stat("symInput.txt", &fileSymStat);
    lstat("symInput.txt", &linkStat);


    // print file info
    printf("File mode: %d\n", fileStat.st_mode); // file permissions and mode
    printf("File size (in block): %ld \n", fileStat.st_blksize);
    printf("File size (in block of 512 byte): %ld \n", fileStat.st_blocks);
    printf("File size (in byte): %ld \n", fileStat.st_size);
    printf("Hardlink counter: %ld \n", fileStat.st_nlink);
    printf("User ID: %d \n", fileStat.st_uid);
    printf("Group ID: %d \n", fileStat.st_gid);
    printf("Filestytem ID: %ld \n", fileStat.st_dev);
    printf("Last access timestamp: %ld \n", fileStat.st_atim.tv_sec);

    // use macro to get file mode info
    printf("\nIs a directory? ");
    (S_ISDIR(fileStat.st_mode)) ? printf("Yes\n") : printf("No\n");

    printf("Has special char? ");
    (S_ISCHR(fileStat.st_mode)) ? printf("Yes\n") : printf("No\n");

    printf("Is a queue? ");
    (S_ISFIFO(fileStat.st_mode)) ? printf("Yes\n") : printf("No\n");

    printf("Is a regular file? ");
    (S_ISREG(fileStat.st_mode)) ? printf("Yes\n") : printf("No\n");

    printf("Is a sym-link? ");
    (S_ISLNK(fileStat.st_mode)) ? printf("Yes\n") : printf("No\n");

    printf("Is a special file? ");
    (S_ISBLK(fileStat.st_mode)) ? printf("Yes\n") : printf("No\n");

    printf("Is a socket file? ");
    (S_ISSOCK(fileStat.st_mode)) ? printf("Yes\n") : printf("No\n");

    printf("\nPrint file info via link \n");
    printf("File mode: %d\n", fileSymStat.st_mode);                 // file permissions and mode
    printf("File size (in block): %ld \n", fileSymStat.st_blksize);
    printf("File size (in block of 512 byte): %ld \n", fileSymStat.st_blocks);
    printf("File size (in byte): %ld \n", fileSymStat.st_size);
    printf("Hardlink counter: %ld \n", fileSymStat.st_nlink);
    printf("User ID: %d \n", fileSymStat.st_uid);
    printf("Group ID: %d \n", fileSymStat.st_gid);
    printf("Filestytem ID: %ld \n", fileSymStat.st_dev);
    printf("Last access timestamp: %ld \n", fileSymStat.st_atim.tv_sec);

    printf("\nPrint link info\n");
    printf("File mode: %d\n", linkStat.st_mode);                    // file permissions and mode
    printf("File size (in block): %ld \n", linkStat.st_blksize);
    printf("File size (in block of 512 byte): %ld \n", linkStat.st_blocks);
    printf("File size (in byte): %ld \n", linkStat.st_size);
    printf("Hardlink counter: %ld \n", linkStat.st_nlink);
    printf("User ID: %d \n", linkStat.st_uid);
    printf("Group ID: %d \n", linkStat.st_gid);
    printf("Filestytem ID: %ld \n", linkStat.st_dev);
    printf("Last access timestamp: %ld \n", linkStat.st_atim.tv_sec);

    printf("Is a sym-link? ");
    (S_ISLNK(linkStat.st_mode)) ? printf("Yes\n") : printf("No\n");

}