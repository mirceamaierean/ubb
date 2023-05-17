// Create two processes A and B. A generates a random number n between 50 and 200. If it is even, it sends it to B, if it is odd it sends n+1 to B. B receives the number and divides it by 2 and sends it back to A. The process repeats until n is smaller than 5. The processes will print the value of n at each step.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  int n, p2c[2], c2p[2];

  if (pipe(p2c) < 0)
  {
    perror("pipe");
    exit(1);
  }

  if (pipe(c2p) < 0)
  {
    perror("pipe");
    exit(1);
  }

  int f = fork();
  if (f < 0)
  {
    perror("fork error");
    close(p2c[0]);
    close(p2c[1]);
    close(c2p[0]);
    close(c2p[1]);
    exit(1);
  }
  else if (f == 0)
  {
    close(p2c[1]);
    close(c2p[0]);
    int n;
    while (1)
    {
      if (read(p2c[0], &n, sizeof(int)) < 0)
      {
        perror("b: read error");
        exit(1);
      }
      printf("B received %d\n", n);
      n /= 2;
      if (write(c2p[1], &n, sizeof(int)) < 0)
      {
        perror("B: write error");
        exit(1);
      }
      printf("B sent %d\n", n);
      if (n < 5)
        break;
    }
    close(p2c[0]);
    close(c2p[1]);
    exit(0);
  }
  else
  {
    srandom(getpid());

    close(p2c[0]);
    close(c2p[1]);

    n = random() % 151 + 50;
    printf("A generated %d\n", n);
    while (n >= 5)
    {
      if (n % 2 == 1)
        n++;
      if (write(p2c[1], &n, sizeof(int)) < 0)
      {
        perror("A: write error");
        exit(1);
      }
      printf("A sent %d\n", n);
      if (read(c2p[0], &n, sizeof(int)) < 0)
      {
        perror("A: read error");
        exit(1);
      }
      printf("A received %d\n", n);
    }
    wait(NULL);
    close(p2c[1]);
    close(c2p[0]);
  }

  return 0;
}