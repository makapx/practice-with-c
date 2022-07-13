/*
    Homework n.1
    Scrivere un programma in linguaggio C che permetta di copiare un numero
    arbitrario di file regolari su una directory di destinazione preesistente.
    Il programma dovra' accettare una sintassi del tipo:
    $ homework-1 file1.txt path/file2.txt "nome con spazi.pdf" directory-destinazione
*/

#include <stdio.h>     //standard library
#include <unistd.h>    //POSIX API
#include <stdlib.h>    //standard library
#include <sys/fcntl.h> //file costants
#include <string.h>    //for string manipulation

int main(int argc, char **argv)
{
    const int BUFFSIZE = 1024; // buffer size
    char buffer[BUFFSIZE];     // buffer
    char newPathname[BUFFSIZE];
    // checking number of args
    if (argc < 3)
    {
        printf("use: %s <source_file> <destination>", argv[0]);
        exit(1);
    }

    printf("Coping...\n");
    for (int i = 1; i < argc - 1; i++)
    {
        // open each file in read only
        int fd = open(argv[i], O_RDONLY);
        if (fd == -1)
        {
            fprintf(stderr, "Error in opening file %s \n", argv[i]);
            exit(1);
        }

        char *tokens = strtok(argv[i], "/");
        char *filename;
        // strtok return first token on first call and pointer to next token passing NULL
        do
        {
            filename = tokens;
        } while ((tokens = strtok(NULL, "/")) != NULL);
        // first time using do while in my life lmao

        memset(newPathname, '\0', strlen(argv[argc - 1]) + strlen(filename));
        // copy file in this directory
        if (strcmp(argv[argc - 1], ".") == 0)
        {
            strcpy(newPathname, filename);
        }
        else
        {
            // use absolute dir path
            strcpy(newPathname, argv[argc - 1]);
            strncat(newPathname, "/", sizeof("/"));
            strncat(newPathname, filename, strlen(filename));
        }

        int newFd = open(newPathname, O_RDWR | O_CREAT, 0660);
        if (newFd == -1)
        {
            printf("Error in copying %s", argv[i]);
            exit(1);
        }
        int readed;
        while ((readed = read(fd, buffer, BUFFSIZE)) != -1 && readed != 0)
        {
            int writed = write(newFd, buffer, readed);
            if (writed == -1)
            {
                int position = lseek(fd, 0, SEEK_CUR);
                printf("Error in writing block %d for file %s \n", position, argv[i]);
                exit(1);
            }
        }
        close(newFd);
        close(fd);
    }

    printf("All files have been copied with success!\n");
}