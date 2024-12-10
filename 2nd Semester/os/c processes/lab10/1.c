// Write a C program that creates a child process. The child process will read two square matrixes of integers from a file. The child process will calculate the product of the two matrixes and send the result matrix to the parent process which will then display it.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
  int c2p[2];
  if (pipe(c2p) < 0)
  {
    perror("pipe");
    exit(1);
  }
  int f = fork();
  if (f < 0)
  {
    perror("fork error");
    close(c2p[0]);
    close(c2p[1]);
    exit(1);
  }
  else if (f == 0)
  {
    // Child code
    close(c2p[0]);
    FILE *f = fopen(argv[1], "r");
    int n, **m1, **m2, **m3;
    fscanf(f, "%d", &n);

    m1 = (int **)malloc(n * sizeof(int *));
    m2 = (int **)malloc(n * sizeof(int *));
    m3 = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; ++i)
    {
      m1[i] = (int *)malloc(n * sizeof(int));
      m2[i] = (int *)malloc(n * sizeof(int));
      m3[i] = (int *)malloc(n * sizeof(int));
      memset(m3[i], 0, n * sizeof(int));
    }

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        fscanf(f, "%d", &m1[i][j]);

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        fscanf(f, "%d", &m2[i][j]);

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        for (int k = 0; k < n; ++k)
          m3[i][j] += m1[i][k] * m2[k][j];

    if (write(c2p[1], &n, sizeof(int)) < 0)
    {
      close(c2p[1]);
      perror("write");
      for (int i = 0; i < n; ++i)
      {
        free(m1[i]);
        free(m2[i]);
        free(m3[i]);
      }
      free(m1);
      free(m2);
      free(m3);
      exit(1);
    }
    for (int i = 0; i < n; ++i)
    {
      if (write(c2p[1], m3[i], n * sizeof(int)) < 0)
      {
        close(c2p[1]);
        perror("write");
        for (int i = 0; i < n; ++i)
        {
          free(m1[i]);
          free(m2[i]);
          free(m3[i]);
        }
        free(m1);
        free(m2);
        free(m3);
        exit(1);
      }
    }
    for (int i = 0; i < n; ++i)
    {
      free(m1[i]);
      free(m2[i]);
      free(m3[i]);
    }
    free(m1);
    free(m2);
    free(m3);
    close(c2p[1]);
    exit(0);
  }
  else
  {
    // Parent code
    close(c2p[1]);
    int n, **m3;
    if (read(c2p[0], &n, sizeof(int)) < 0)
    {
      close(c2p[0]);
      perror("read");
      exit(1);
    }
    m3 = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i)
    {
      m3[i] = (int *)malloc(n * sizeof(int));
      if (read(c2p[0], m3[i], n * sizeof(int)) < 0)
      {
        close(c2p[0]);
        perror("read");
        for (int i = 0; i < n; ++i)
          free(m3[i]);
        free(m3);
        exit(1);
      }
    }
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < n; ++j)
        printf("%d ", m3[i][j]);
      printf("\n");
    }
    for (int i = 0; i < n; ++i)
      free(m3[i]);
    free(m3);
    close(c2p[0]);
    wait(NULL);
  }
  return 0;
}