// Write a C program that takes as command-line arguments 2 numbers: N and M. The program will create N threads and simulate a race where each thread must pass through the M checkpoints. Through each checkpoint, the threads must pass one at a time (no 2 threads can be inside the same checkpoint at the same time). Each thread that enters a checkpoint will wait a random amount of time between 100 and 200 milliseconds (usleep(100000) makes a thread or process wait for 100 milliseconds) and will print a message indicating the thread number and the checkpoint number, then it will exit the checkpoint. Ensure that each thread waits until all threads have been created before starting the race.
#include "../barrier.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct
{
  int id, M;
  pthread_mutex_t *mtx;
  pthread_barrier_t *barr;
} data;

void *f(void *a)
{
  data arg = *((data *)a);
  printf("Thread %d is waiting\n", arg.id);

  pthread_barrier_wait(arg.barr);

  for (int i = 0; i < arg.M; ++i)
  {
    pthread_mutex_lock(&arg.mtx[i]);
    printf("Thread %d at checkpoint %d\n", arg.id, i);
    usleep(random() % 100000 + 100000);
    pthread_mutex_unlock(&arg.mtx[i]);
  }
  printf("Thread %d finished\n", arg.id);
  return NULL;
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    perror("provide exactly 2 numbers\n");
    exit(1);
  }
  int N = atoi(argv[1]);
  int M = atoi(argv[2]);

  // Create barrier;
  pthread_barrier_t barr;
  if (pthread_barrier_init(&barr, NULL, N))
  {
    perror("error barrier\n");
    exit(1);
  }

  // Create mutexes
  pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t) * M);

  for (int i = 0; i < M; ++i)
    if (pthread_mutex_init(&mtx[i], NULL))
    {
      pthread_barrier_destroy(&barr);
      for (int j = 0; j < i; ++i)
        pthread_mutex_destroy(&mtx[i]);
      free(mtx);
    }

  srand(time(NULL));

  data *args = malloc(sizeof(data) * N);
  pthread_t *th = malloc(sizeof(pthread_t) * N);
  for (int i = 0; i < N; ++i)
  {
    args[i].id = i;
    args[i].mtx = mtx;
    args[i].barr = &barr;
    args[i].M = M;
    if (pthread_create(&th[i], NULL, f, &args[i]))
    {
      perror("error creating thread\n");
      exit(1);
    }
  }

  for (int i = 0; i < N; ++i)
    pthread_join(th[i], NULL);

  for (int i = 0; i < M; ++i)
    pthread_mutex_destroy(&mtx[i]);

  pthread_barrier_destroy(&barr);

  free(args);
  free(th);
  free(mtx);

  return 0;
}