/**
 * @file 17_exec.c
 * @author makapx (https://github.com/makapx)
 * @brief process, execv, execl
 * @version 0.1
 * @date 2022-07-17
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    fork();
    // execl("/usr/bin/man", "/usr/bin/man", "execl", NULL);

    char *const args[] = {"/usr/bin/man", "execv", NULL};
    execv("/usr/bin/man", args);
}