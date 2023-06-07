// Write a program that receives strings of characters as command line arguments. For each string the program creates a thread which calculates the number of digits, the number of leters and the number of special characters (anything other than a letter or digit). The main program waits for the threads to terminate and prints the total results (total number of digits, letters and special characters across all the received command line arguments) and terminates. Use efficient synchronization. Do not use global variables
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
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
  int index;
  for (int i = 0; arg.str[i]; ++i)
  {
    index = 0;
    arg.str[i] = tolower(arg.str[i]);
    if (arg.str[i] >= 'a' && arg.str[i] <= 'z')
      index = 0;
    else if (isdigit(arg.str[i]))
      index = 1;
    else
      index = 2;
    pthread_mutex_lock(&arg.mtxs[index]);
    arg.fr[index] += 1;
    pthread_mutex_unlock(&arg.mtxs[index]);
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    perror("boss mai multe argumente ms\n");
    exit(1);
  }

  // Create mutexes
  pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t) * 3);
  for (int i = 0; i < 3; ++i)
    pthread_mutex_init(&mtx[i], NULL);

  // Create threads and data
  pthread_t *th = malloc(sizeof(pthread_t) * (argc - 1));
  data *arg = malloc(sizeof(data) * (argc - 1));
  int *fr = malloc(sizeof(int) * 3);
  memset(fr, 0, sizeof(int) * 3);

  for (int i = 0; i < argc - 1; ++i)
  {
    arg[i].fr = fr;
    arg[i].mtxs = mtx;
    arg[i].str = argv[i + 1];
    if (pthread_create(&th[i], NULL, f, &arg[i]))
      perror("error thread");
  }

  for (int i = 0; i < argc - 1; ++i)
    pthread_join(th[i], NULL);

  printf("Letters: %d\nDigits: %d\nSpecials: %d\n", fr[0], fr[1], fr[2]);

  for (int i = 0; i < 3; ++i)
    pthread_mutex_destroy(&mtx[i]);

  free(mtx);
  free(fr);
  free(arg);
  free(th);

  return 0;
}