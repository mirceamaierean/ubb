#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define BUF_LEN 100

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Provide at least one argument");
    exit(1);
  }
  int fd[2];
  if (pipe(fd) < 0)
  {
    perror("Error creating pipe");
    exit(1);
  }
  int f = fork();
  if (f == 0)
  {
    printf("Child process\n");
    close(fd[0]);
    int copy_fd = dup(1);
    if (dup2(fd[1], 1) < 0)
    {
      perror("Error on dup stdout");
      exit(1);
    }
    if (execvp(argv[1], argv + 1) == -1)
    {
      perror("Error executing command");
      if (dup2(copy_fd, 1) < 0)
        perror("Error on dup stdout");
      exit(1);
    }
    exit(0);
  }
  else
  {
    close(fd[1]);
    char *buf = malloc(sizeof(char) * BUF_LEN);
    memset(buf, 0, sizeof(char) * BUF_LEN);
    int k;
    while ((k = read(fd[0], buf, sizeof(char) * BUF_LEN)) > 0)
    {
      printf("%s", buf);
      memset(buf, 0, sizeof(char) * BUF_LEN);
    }
    free(buf);
    wait(NULL);
    close(fd[0]);
  }
  return 0;
}