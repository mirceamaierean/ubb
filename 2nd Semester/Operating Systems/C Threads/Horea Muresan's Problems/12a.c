// Write a C program that reads a matrix of integers from a file. It then creates as many threads as there are rows in the matrix, each thread calculates the sum of the numbers on a row. The main process waits for the threads to finish, then prints the sums.
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  int id;
  int len;
  int *arr;
  int *sum;
} data;

void *func(void *a)
{
  data arg = *((data *)a);
  for (int i = 0; i < arg.len; ++i)
    *(arg.sum) += arg.arr[i];

  return NULL;
}

int main(int argc, char *argv[])
{
  FILE *f = fopen("matrix.txt", "r");

  int n, m;
  fscanf(f, "%d%d", &n, &m);

  int **mat = malloc(sizeof(int *) * n);

  for (int i = 0; i < n; ++i)
  {
    mat[i] = malloc(sizeof(int) * m);
    for (int j = 0; j < m; ++j)
      fscanf(f, "%d", &mat[i][j]);
  }

  // Create data for threads;
  pthread_t *th = malloc(sizeof(pthread_t) * n);
  data *arg = malloc(sizeof(data) * n);

  for (int i = 0; i < n; ++i)
  {
    arg[i].id = i;
    arg[i].len = m;
    arg[i].arr = mat[i];
    arg[i].sum = malloc(sizeof(int));
    *(arg[i].sum) = 0;
    if (pthread_create(&th[i], NULL, func, &arg[i]))
      perror("boss bai la thread");
  }

  for (int i = 0; i < n; ++i)
    pthread_join(th[i], NULL);

  int sum = 0;
  for (int i = 0; i < n; ++i)
  {
    printf("Thread %d sum %d\n", arg[i].id, *(arg[i].sum));
    sum += *(arg[i].sum);
    free(arg[i].sum);
    free(mat[i]);
  }

  printf("total sum %d", sum);

  free(arg);
  free(mat);
  free(th);

  fclose(f);

  return 0;
}