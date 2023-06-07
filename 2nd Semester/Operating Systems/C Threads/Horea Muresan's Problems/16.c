// Write a C program that receives integers as command line argument. The program will keep a frequency vector for all digits. The program will create a thread for each argument that counts the number of occurences of each digit and adds the result to the frequency vector. Use efficient synchronization.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>

typedef struct
{
  int *fr;
  pthread_mutex_t *mtxs;
  char *str;
} data;

void *f(void *a)
{
  data arg = *((data *)a);

  for (int i = 0; arg.str[i]; ++i)
  {
    int index = arg.str[i] - '0';
    pthread_mutex_lock(&arg.mtxs[index]);
    ++arg.fr[index];
    pthread_mutex_unlock(&arg.mtxs[index]);
  }

  return NULL;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    perror("provide arguments");
    exit(1);
  }

  // Create mutexes
  pthread_mutex_t *mtxs = malloc(sizeof(pthread_mutex_t) * 10);

  // Init mutexes
  for (int i = 0; i < 10; ++i)
    pthread_mutex_init(&mtxs[i], NULL);

  // Create threads
  pthread_t *th = malloc(sizeof(pthread_t) * (argc - 1));

  // Create data
  int *fr = malloc(sizeof(int) * 10);
  memset(fr, 0, sizeof(int) * 10);

  data *arg = malloc(sizeof(data) * (argc - 1));
  for (int i = 0; i < argc - 1; ++i)
  {
    arg[i].fr = fr;
    arg[i].str = argv[i + 1];
    arg[i].mtxs = mtxs;
    if (pthread_create(&th[i], NULL, f, &arg[i]))
      perror("error thread");
  }

  for (int i = 0; i < argc - 1; ++i)
    pthread_join(th[i], NULL);

  for (int i = 0; i <= 9; ++i)
    printf("fr[%d]: %d\n", i, fr[i]);

  for (int i = 0; i < 10; ++i)
    pthread_mutex_destroy(&mtxs[i]);

  free(fr);
  free(arg);
  free(th);
  free(mtxs);

  return 0;
}
