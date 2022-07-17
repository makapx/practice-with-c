/**
 * @file 16_process.c
 * @author makapx (https://github.com/makapx)
 * @brief process, fork
 * @version 0.1
 * @date 2022-07-17
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Error in fork child");
        exit(1);
    }

    (pid == 0) ? printf("Hello from child, my mother is %d \n", getppid()) : printf("Hello from mother, my child is %d\n", pid);

    if (pid == 0)
    {
        for (int i = 0; i < 10000; i++)
        {
            // do something
        }
        printf("Child: My job here is done\n");
        exit(1);
    }
    else
    {
        wait(NULL); // wait for child to die
        printf("Mother: Oh, he died. BTW...\n");
    }

    printf("Mother: Forked 3 children\n");
    pid_t firstChild = fork();
    if (firstChild != 0)
    {
        printf("Mother: my first (not so first) child is born\n");
        waitpid(firstChild, NULL, 0); // wait for first child
        pid_t middleChild = fork();
        if (middleChild != 0)
        {
            printf("Mother: My middle child is born\n");
            waitpid(middleChild, NULL, 0); // wait for middle child
            pid_t lastChild = fork();
            if (lastChild != 0)
            {
                printf("Mother: My last child is born\n");
                waitpid(lastChild, NULL, 0); // wait for last child
            }
            else
            {
                printf("Last child: Why mother?\n");
            }
        }
        else
        {
            printf("Middle child: R u serius?\n");
        }
    }
    else
    {
        printf("First child: Welp\n");
    }
}