// Write a C program that receives strings containing any characters as command-line arguments. The program will create a frequency vector for all lowercase letters of the alphabet. The program will create a thread for each command-line argument, each thread will update the letter frequency vector based on the characters present in its corresponding command-line argument. Use efficient synchronization.
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
  int id;
  char *word;
  int *fr_vect;
  pthread_mutex_t *mtx;
} data;

// Create function for thread
void *f(void *a)
{
  // Convert data
  data arg = *((data *)a);
  printf("Thread %d with id works with word: %s\n", arg.id, arg.word);
  for (int i = 0; arg.word[i]; ++i)
  {
    if (arg.word[i] >= 'a' && arg.word[i] <= 'z')
    {
      int pos = arg.word[i] - 'a';
      pthread_mutex_lock(&arg.mtx[pos]);
      ++arg.fr_vect[pos];
      pthread_mutex_unlock(&arg.mtx[pos]);
    }
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    perror("provide at least a word");
    exit(1);
  }
  // Create mutexes;
  int size = 'z' - 'a' + 1;
  pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t) * size);

  for (int i = 0; i < size; ++i)
    pthread_mutex_init(&mtx[i], NULL);

  // Create threads and datas;
  data *arg = malloc(sizeof(data) * (argc - 1));
  int *freq = malloc(sizeof(int) * size);
  memset(freq, 0, sizeof(int) * size);

  pthread_t *th = malloc(sizeof(pthread_t) * (argc - 1));

  for (int i = 0; i < argc - 1; ++i)
  {
    arg[i].id = i;
    arg[i].fr_vect = freq;
    arg[i].word = argv[i + 1];
    arg[i].mtx = mtx;
    if (pthread_create(&th[i], NULL, f, &arg[i]))
    {
      perror("error creating thread");
      exit(1);
    }
  }

  for (int i = 0; i < argc - 1; ++i)
    pthread_join(th[i], NULL);

  for (int i = 0; i < size; ++i)
  {
    if (freq[i])
      printf("%c: %d\n", (char)i + 'a', freq[i]);
    pthread_mutex_destroy(&mtx[i]);
  }

  free(mtx);
  free(arg);
  free(freq);
  free(th);

  return 0;
}