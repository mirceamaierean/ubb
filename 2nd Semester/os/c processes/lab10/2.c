#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main(int argc, char *argv[])
{
  int n = argc - 1, **c2p;
  c2p = malloc(sizeof(int *) * n);

  for (int i = 0; i < n; i++)
    c2p[i] = malloc(sizeof(int) * 2);

  for (int i = 0; i < n; i++)
    if (pipe(c2p[i]) < 0)
    {
      perror("Error creating pipes");
      exit(1);
    }

  int total_len = 0;
  for (int i = 0; i < n; i++)
  {
    // calculate the total length of the result -> sum of the lengths of all arguments + 1 for the NULL terminator
    total_len += strlen(argv[i + 1]);
    int f = fork();
    if (f < 0)
      perror("Error on fork");
    else if (f == 0)
    {
      //  close all the read ends of the pipes, except the one we're using
      for (int j = 0; j < n; j++)
      {
        close(c2p[j][0]);
        if (j != i)
          close(c2p[j][1]);
      }
      // we can create a copy of the argument if we want, but since the child has access to a copy of the command line arguments anyway, might as well use them
      int len = strlen(argv[i + 1]);
      for (int j = 0; argv[i + 1][j]; j++)
        argv[i + 1][j] = toupper(argv[i + 1][j]);

      if (0 > write(c2p[i][1], argv[i + 1], sizeof(char) * len))
      {
        perror("Error while sending the modified argument from the child process");
        close(c2p[i][1]);
        exit(1);
      }
      close(c2p[i][1]);
      exit(0);
    }
  }
  char *result = malloc(sizeof(char) * (total_len + 1));
  memset(result, 0, sizeof(char) * (total_len + 1));
  for (int i = 0; i < n; i++)
  {
    int len = strlen(argv[i + 1]);

    char *buf = malloc(sizeof(char) * (len + 1));

    if (read(c2p[i][0], buf, sizeof(char) * len) < 0)
      perror("Error reading argument in parent process");

    else
    {
      buf[len] = 0;
      strcat(result, buf);
    }
    free(buf);
    wait(0);
  }
  printf("%s\n", result);

  for (int i = 0; i < n; i++)
    free(c2p[i]);

  free(c2p);
  free(result);
  return 0;
}
