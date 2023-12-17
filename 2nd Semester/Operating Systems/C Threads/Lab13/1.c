// write a c program that creates 3 threads. the threads will keep adding random numbers between -500 and 500 to a shared variable that initially has value 0.
// the threads will terminate when the shared variable has a value greater than 500
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct
{
  int id;
  int *num;
  pthread_mutex_t *mtx;
} data;

void *f(void *a)
{
  data arg = *((data *)a);
  while (1)
  {
    if (abs(*arg.num) > 500)
    {
      printf("Thread %d detected a valuea greater than 500\n", arg.id);
      break;
    }
    printf("Thread %d locks mutex\n", arg.id);
    pthread_mutex_lock(arg.mtx);
    int nr = random() % 1001 - 500;
    *(arg.num) += nr;
    printf("Thread %d added %d, with final value %d\n", arg.id, nr, *(arg.num));
    printf("Thread %d unlocks mutex\n", arg.id);
    pthread_mutex_unlock(arg.mtx);
    usleep(100);
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  srandom(getpid());
  // Create Mutex
  pthread_mutex_t mtx;
  pthread_mutex_init(&mtx, NULL);

  // Create threads and data
  int thcnt = 3;
  pthread_t *th = malloc(sizeof(pthread_t) * thcnt);
  data *args = malloc(sizeof(data) * thcnt);
  int *n = malloc(sizeof(int));
  *n = 0;

  for (int i = 0; i < thcnt; ++i)
  {
    args[i].id = i;
    args[i].num = n;
    args[i].mtx = &mtx;
    if (pthread_create(&th[i], NULL, f, &args[i]))
    {
      perror("not good\n");
      exit(1);
    }
  }

  for (int i = 0; i < thcnt; ++i)
    pthread_join(th[i], NULL);

  pthread_mutex_destroy(&mtx);
  free(th);

  return 0;
}