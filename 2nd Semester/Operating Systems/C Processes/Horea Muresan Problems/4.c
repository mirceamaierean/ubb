// Write a C program that runs a bash command (potentially with arguments) received as a command line argument and times its execution.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
  struct timeval start, end;
  if (argc < 2)
  {
    perror("Error on arguments");
    exit(1);
  }
  gettimeofday(&start, NULL);
  int f = fork();
  if (f < 0)
  {
    perror("Error on fork");
    exit(1);
  }
  else if (f == 0)
  {
    if (execvp(argv[1], argv + 1) < 0)
    {
      perror("Error on exec");
      exit(1);
    }
  }
  else
  {
    wait(NULL);
    gettimeofday(&end, NULL);
    printf("Time elapsed in microseconds: %ld\n", (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);
  }
  return 0;
}