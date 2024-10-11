#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
  {
    int f = fork();
    if (f < 0)
    {
      perror("Error on fork");
      exit(1);
    }
    if (f == 0)
    {
      printf("Child: %d PID: %d, PPID: %d\n", i, getpid(), getppid());
      exit(0);
    }
  }
  for (int i = 1; i <= n; ++i)
    wait(NULL);

  printf("Parent PID: %d\n", getpid());
  return 0;
}
