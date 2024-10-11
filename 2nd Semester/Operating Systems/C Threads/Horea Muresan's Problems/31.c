// Write a C program that receives a number N as a command-line argument. The program creates N threads that will generate random numbers between 0 and 111111 (inclusive) until one thread generates a number divisible by 1001. The threads will display the generated numbers, but the final number that is displayed must be the one that is divisible by 1001. No thread will start generating random numbers until all threads have been created. Do not use global variables.
#include "../barrier.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
  int id;
  int *nr;
  pthread_mutex_t *mtx;
  pthread_barrier_t *barr;
} data;

void *f(void *a)
{
  data arg = *((data *)a);
  pthread_barrier_wait(arg.barr);
  while (1)
  {
    pthread_mutex_lock(arg.mtx);
    printf("Thread %d read value %d\n", arg.id, *(arg.nr));
    int nr = *(arg.nr);
    if (nr % 1001 == 0)
      break;
    nr = random() % 111112;
    *(arg.nr) = nr;
    pthread_mutex_unlock(arg.mtx);
  }
  pthread_mutex_unlock(arg.mtx);
  return NULL;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    perror("provide number of arguments");
    exit(1);
  }

  srand(getpid());

  int n = atoi(argv[1]);

  // Create mutex
  pthread_mutex_t mtx;
  if (pthread_mutex_init(&mtx, NULL))
  {
    perror("error mutex");
    exit(1);
  }

  // Create barrier
  pthread_barrier_t barr;
  if (pthread_barrier_init(&barr, NULL, n))
  {
    perror("error barrier");
    exit(1);
  }

  // Create threads
  pthread_t *th = malloc(sizeof(pthread_t) * n);

  // Create data
  data *arg = malloc(sizeof(data) * n);
  int *nr = malloc(sizeof(int));
  *nr = 1;

  for (int i = 0; i < n; ++i)
  {
    arg[i].id = i;
    arg[i].mtx = &mtx;
    arg[i].barr = &barr;
    arg[i].nr = nr;
    if (pthread_create(&th[i], NULL, f, &arg[i]))
    {
      perror("error thread");
      exit(1);
    }
  }

  for (int i = 0; i < n; ++i)
    pthread_join(th[i], NULL);

  printf("Final number: %d\n", *nr);

  pthread_barrier_destroy(&barr);
  pthread_mutex_destroy(&mtx);

  free(nr);
  free(arg);
  free(th);

  return 0;
}