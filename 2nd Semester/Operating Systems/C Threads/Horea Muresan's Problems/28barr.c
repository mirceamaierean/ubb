// Write a C program that reads a number n from standard input and generates an array s of n random integers between 0 and 1000. After the array is created, the main process creates n + 1 threads.Each of the first n threads repeats the following steps until the array is sorted in ascending order:
#include <stdio.h>
#include "../barrier.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
  int len;
  int *arr;
  pthread_mutex_t *mtx;
  pthread_barrier_t *barr;
} data;

void *f(void *a)
{
  data arg = *((data *)a);
  while (1)
  {
    pthread_mutex_lock(arg.mtx);
    int sorted = 1;
    for (int i = 1; i < arg.len; ++i)
      if (arg.arr[i - 1] >= arg.arr[i])
      {
        sorted = 0;
        break;
      }
    for (int i = 0; i < arg.len; ++i)
      printf("%d ", arg.arr[i]);
    printf("\n");
    if (sorted)
      break;
    int i = random() % arg.len, j = random() % arg.len;
    if ((i < j && arg.arr[i] > arg.arr[j]) || (i > j && arg.arr[i] < arg.arr[j]))
    {
      int aux = arg.arr[i];
      arg.arr[i] = arg.arr[j];
      arg.arr[j] = aux;
    }
    pthread_mutex_unlock(arg.mtx);
  }
  pthread_mutex_unlock(arg.mtx);
  pthread_barrier_wait(arg.barr);
  return NULL;
}

void *finalBossFunction(void *a)
{
  data arg = *((data *)a);
  pthread_barrier_wait(arg.barr);
  for (int i = 0; i < arg.len; ++i)
    printf("%d ", arg.arr[i]);
  printf("\n");
  return NULL;
}

int main(int argc, char *argv[])
{
  int n;
  printf("n = ");
  scanf("%d", &n);

  srand(time(NULL));

  int *arr = malloc(sizeof(int) * n);
  for (int i = 0; i < n; ++i)
    arr[i] = random() % 1001;

  // Create mutex
  pthread_mutex_t mtx;
  if (pthread_mutex_init(&mtx, NULL))
  {
    perror("error mutex");
    exit(1);
  }

  // Create barrier
  pthread_barrier_t barr;
  if (pthread_barrier_init(&barr, NULL, n + 1))
  {
    perror("error barrier");
    exit(1);
  }

  // Create threads
  pthread_t *th = malloc(sizeof(pthread_t) * n);
  pthread_t finalBoos;

  // Create data
  data *arg = malloc(sizeof(data) * (n + 1));
  for (int i = 0; i < n; ++i)
  {
    arg[i].len = n;
    arg[i].arr = arr;
    arg[i].mtx = &mtx;
    arg[i].barr = &barr;
    if (pthread_create(&th[i], NULL, f, &arg[i]))
      perror("error thread");
  }
  arg[n].len = n;
  arg[n].arr = arr;
  arg[n].mtx = &mtx;
  arg[n].barr = &barr;
  if (pthread_create(&finalBoos, NULL, finalBossFunction, &arg[n]))
    perror("error thread");

  for (int i = 0; i < n; ++i)
    pthread_join(th[i], NULL);

  pthread_join(finalBoos, NULL);

  pthread_barrier_destroy(&barr);
  pthread_mutex_destroy(&mtx);

  free(arg);
  free(arr);
  free(th);

  return 0;
}