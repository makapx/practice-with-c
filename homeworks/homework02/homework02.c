/*
    Homework n.2

    Estendere l'esempio 'move.c' visto a lezione per supportare i 2 casi speciali:
    - spostamento cross-filesystem: individuato tale caso, il file deve essere
      spostato utilizzando la strategia "copia & cancella";
    - spostamento di un link simbolico: individuato tale caso, il link simbolico
      deve essere ricreato a destinazione con lo stesso contenuto (ovvero il percorso
      che denota l'oggetto referenziato); notate come tale spostamento potrebbe
      rendere il nuovo link simbolico non effettivamente valido.

    La sintassi da supportare e' la seguente:
    $ homework-2 <pathname sorgente> <pathname destinazione>
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <string.h>

/**
 * @brief move regular file
 *
 * @param inFile
 * @param argv
 * @return int
 */
int moveFile(struct stat inFile, char **argv)
{
  // create a util symlink
  if (symlink(argv[1], argv[2]) == -1)
  {
    fprintf(stderr, "Error in creating symlink\n");
    return -1;
  }

  struct stat cpFile;
  lstat(argv[2], &cpFile);

  // check for same file system
  short int toSameFs = (inFile.st_dev == cpFile.st_dev);
  // unlink utils symlink
  unlink(argv[2]);

  // check if they are in the same filesystem
  if (toSameFs & inFile.st_nlink == 1)
  {
    // move file
    link(argv[1], argv[2]);
    unlink(argv[1]);
    return 1;
  }

  // init fds
  int originFile = open(argv[1], O_RDONLY);
  int destinationFile = open(argv[2], O_RDWR | O_TRUNC | O_CREAT, 0660);

  // init buffer
  const int BUFFSIZE = 1024;
  char buffer[BUFFSIZE];

  // readed bytes
  int readed;
  while ((readed = read(originFile, buffer, BUFFSIZE)) != -1 && readed != 0)
  {
    // copy
    if (write(destinationFile, buffer, strlen(buffer)) == -1)
    {
      fprintf(stderr, "Error in writing %s \n", argv[2]);
      return -3;
    }
  }

  // remove origin
  unlink(argv[1]);
  return 1;
}

/**
 * @brief move symlink
 *
 * @param inFile
 * @param argv
 * @return int
 */
int moveSymLink(struct stat inFile, char **argv)
{
  const int BUFFSIZE = 1024;
  char buffer[1024];
  if (readlink(argv[1], buffer, BUFFSIZE) == -1)
  {
    fprintf(stderr, "Error in read link path");
    return -1;
  }

  // creating new link with old path
  if (symlink(buffer, argv[2]) == -1)
  {
    fprintf(stderr, "Error in creating symlink");
    return -2;
  }
  // remove old link
  unlink(argv[1]);
  return 1;
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    fprintf(stderr, "Error: usage cmd <source> <destination>\n");
    exit(1);
  }

  struct stat inFile;
  lstat(argv[1], &inFile);

  if (S_ISLNK(inFile.st_mode))
  {
    moveSymLink(inFile, argv);
    return 1;
  }

  if (S_ISREG(inFile.st_mode))
  {
    moveFile(inFile, argv);
  }
}