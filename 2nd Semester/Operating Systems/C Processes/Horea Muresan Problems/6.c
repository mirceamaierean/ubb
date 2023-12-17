/* Create a C program that generates N random integers (N given at the command line).
 * It then creates a child, sends the numbers via pipe. The child calculates the average and sends the result back.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    perror("provide arguments");
    exit(1);
  }
  int p2c[2], c2p[2];

  if (pipe(p2c) < 0 || pipe(c2p) < 0)
  {
    perror("pipe");
    exit(1);
  }

  int n, *numbers, f = fork();
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
    if (read(p2c[0], &n, sizeof(int)) < 0)
    {
      perror("Child read error");
      close(p2c[0]);
      close(c2p[1]);
      exit(1);
    }
    printf("Child received length %d\n", n);
    numbers = (int *)malloc(n * sizeof(int));
    if (read(p2c[0], numbers, sizeof(int) * n) < 0)
    {
      perror("Child read error");
      close(p2c[0]);
      close(c2p[1]);
      exit(1);
    }
    printf("Child received numbers:");
    float avg = 0;
    for (int i = 0; i < n; ++i)
      avg += numbers[i];
    avg /= n;
    printf("Child calculated average %f\n", avg);
    if (write(c2p[1], &avg, sizeof(float)) < 0)
    {
      perror("Child write error");
      close(p2c[0]);
      close(c2p[1]);
      exit(1);
    }
    close(p2c[0]);
    close(c2p[1]);
    exit(0);
  }
  else
  {
    close(p2c[0]);
    close(c2p[1]);
    n = atoi(argv[1]);
    numbers = (int *)malloc(n * sizeof(int));
    srand(getpid());

    for (int i = 0; i < n; ++i)
      numbers[i] = rand() % 100 + 1;

    if (write(p2c[1], &n, sizeof(int)) < 0)
    {
      perror("Parent write error");
      close(p2c[1]);
      close(c2p[0]);
      exit(1);
    }
    printf("Parent sent length %d\n", n);
    if (write(p2c[1], numbers, sizeof(int) * n) < 0)
    {
      perror("Parent write error");
      close(p2c[1]);
      close(c2p[0]);
      exit(1);
    }
    printf("Parent sent numbers:");
    for (int i = 0; i < n; ++i)
      printf("%d ", numbers[i]);
    printf("\n");
    float avg;
    if (read(c2p[0], &avg, sizeof(float)) < 0)
    {
      perror("Parent read error");
      close(p2c[1]);
      close(c2p[0]);
      exit(1);
    }
    printf("Parent received average %f\n", avg);
    close(p2c[1]);
    close(c2p[0]);
    free(numbers);
    wait(0);
  }

  return 0;
}