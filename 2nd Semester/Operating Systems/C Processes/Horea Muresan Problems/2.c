// Write a C program that creates a linear hierarchy of n processes (a parent process creates a child process, which in turn creates a child process, and so on).
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void func(int n)
{
  if (n)
  {
    int f = fork();
    if (f < 0)
    {
      perror("Error on fork");
      exit(1);
    }
    else if (f == 0)
    {
      printf("PID: %d, PPID: %d\n", getpid(), getppid());
      func(n - 1);
    }
  }
  wait(NULL);
  exit(0);
}

int main()
{
  int n;
  printf("n = ");
  scanf("%d", &n);
  func(n);
  return 0;
}