// Write a C program that reads a number N and creates 2 threads. One of the threads will generate an even number and will append it to an array that is passed as a parameter to the thread. The other thread will do the same, but using odd numbers. Implement a synchronization between the two threads so that they alternate in appending numbers to the array, until they reach the maximum length N.
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define TH_NR 2

typedef struct
{
  int id;
  int *index;
  int *arr;
  int max_size;
  pthread_mutex_t *mtx;
  pthread_cond_t *cond;
} data;

void *f(void *a)
{
  data arg = *((data *)a);
  while (1)
  {
    pthread_mutex_lock(arg.mtx);

    int nr = 2 * (random() % 100) + arg.id;
    printf("Thread %d index %d value %d\n", arg.id, *(arg.index), nr);

    while (arg.id != (*(arg.index) % 2))
      pthread_cond_wait(arg.cond, arg.mtx);

    if (*(arg.index) >= arg.max_size)
    {
      *(arg.index) += 1;
      break;
    }
    arg.arr[*(arg.index)] = nr;
    *(arg.index) += 1;
    pthread_cond_signal(arg.cond);
    pthread_mutex_unlock(arg.mtx);
  }
  pthread_cond_signal(arg.cond);
  pthread_mutex_unlock(arg.mtx);

  return NULL;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    perror("please provide an argument\n");
    exit(1);
  }

  int max_size = atoi(argv[1]);

  // Create mutex and cond
  pthread_mutex_t mtx;
  pthread_cond_t cond;

  srandom(getpid());

  pthread_mutex_init(&mtx, NULL);
  pthread_cond_init(&cond, NULL);

  // Create threads
  pthread_t th[TH_NR];
  data *arg = malloc(sizeof(data) * TH_NR);
  int *index = malloc(sizeof(int));
  *index = 0;
  int *arr = malloc(sizeof(int) * max_size);
  memset(arr, 0, sizeof(int) * max_size);

  for (int i = 0; i < TH_NR; ++i)
  {
    arg[i].id = i;
    arg[i].mtx = &mtx;
    arg[i].index = index;
    arg[i].cond = &cond;
    arg[i].max_size = max_size;
    arg[i].arr = arr;
    if (pthread_create(&th[i], NULL, f, &arg[i]))
      perror("boss eroare la thread");
  }

  pthread_join(th[0], NULL);
  pthread_join(th[1], NULL);

  for (int i = 0; i < max_size; ++i)
    printf("%d ", arr[i]);

  pthread_mutex_destroy(&mtx);
  pthread_cond_destroy(&cond);

  free(arr);
  free(index);
  free(arg);

  return 0;
}