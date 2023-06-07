#include "barrier.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct
{
  int id;
  pthread_mutex_t *mutex;
  pthread_barrier_t *barr;
  int *num;
} data;

void *f(void *a)
{
  data d = *((data *)a);
  printf("Thread %d starting...\n", d.id);
  pthread_barrier_wait(d.barr);
  for (int i = 0; i < 100; ++i)
  {
    pthread_mutex_lock(d.mutex);
    (*d.num)++;
    pthread_mutex_unlock(d.mutex);
  }
  printf("Thread %d finished...\n", d.id);
  int *x = malloc(sizeof(int));
  *x = random() % 100;
  return x;
}

int main(int argc, char *argv[])
{
  int numberOfThreads = 10;

  if (argc >= 2)
    numberOfThreads = atoi(argv[1]);

  pthread_mutex_t *mutex = malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(mutex, NULL);

  pthread_barrier_t *barr = malloc(sizeof(pthread_barrier_t));
  pthread_barrier_init(barr, NULL, numberOfThreads);

  data *d = malloc(sizeof(data) * numberOfThreads);

  int *num = malloc(sizeof(int));
  *num = 0;

  pthread_t *threads = malloc(sizeof(pthread_t) * numberOfThreads);
  for (int i = 0; i < numberOfThreads; ++i)
  {
    d[i].id = i + 1;
    d[i].mutex = mutex;
    d[i].barr = barr;
    d[i].num = num;
    if (pthread_create(&threads[i], NULL, f, &d[i]))
    {
      perror("Error creating thread");
      exit(1);
    }
  }

  for (int i = 0; i < numberOfThreads; ++i)
  {
    int *x;
    pthread_join(threads[i], (void **)&x);
    printf("Thread %d genereated %d and value for num is %d\n", i + 1, *x, *d[i].num);
    free(x);
  }

  pthread_mutex_destroy(mutex);
  pthread_barrier_destroy(barr);

  free(threads);
  free(mutex);
  free(barr);
  free(d);
  free(num);
  return 0;
}