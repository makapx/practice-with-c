/**
 * @file 12_fileStatTimeGroup.c
 * @author makapx (https://github.com/makapx)
 * @brief get time and group info from stat
 * @version 0.1
 * @date 2022-07-15
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>      //required for localtime and asctime
#include <sys/types.h> //required for passwd
#include <pwd.h>       //required for passwd
#include <grp.h>       // required for group

int main()
{
    struct stat fileStat;
    stat("input.txt", &fileStat);

    printf("Last access: %s", asctime(localtime(&(fileStat.st_atime))));

    // get file group info
    struct group *groupId = getgrgid(fileStat.st_gid);
    printf("Group ID: %d | Group name: %s | Grop passwd: %s | Group members: %s\n", groupId->gr_gid, groupId->gr_name, groupId->gr_passwd, *groupId->gr_mem);

    // get passwd info for current user
    struct passwd *passwdInfo = getpwuid(fileStat.st_uid);
    if (passwdInfo)
    {
        printf("Passwd username: %s \n", passwdInfo->pw_name);
        printf("Passwd user path info: %s \n", passwdInfo->pw_dir);
        printf("Passwd hash: %s \n", passwdInfo->pw_passwd);
    }
}