/*
   Using PIPE channels create and implement the following scenario:
   Process A reads N integer numbers from the keyboard and sends them another process named B.
   Process B will add a random number, between 2 and 5, to each received number from process A and will send them to another process named C.
   Process C will add all the received numbers and will send the result back to process A. All processes will print a debug message before sending and after receiving a number.

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int a2b[2], b2c[2], c2a[2];
  if (pipe(a2b) < 0 || pipe(b2c) < 0 || pipe(c2a) < 0)
  {
    perror("Error on opening pipe");
    exit(1);
  }
  int n, *numbers;
  scanf("%d", &n);
  numbers = (int *)malloc(n * sizeof(int));
  int f1 = fork();
  if (f1 < 0)
  {
    perror("Error on fork");
    close(a2b[0]);
    close(a2b[1]);
    close(b2c[0]);
    close(b2c[1]);
    close(c2a[0]);
    close(c2a[1]);
    free(numbers);
    exit(1);
  }
  else if (f1 == 0)
  {
    close(a2b[1]);
    close(b2c[0]);
    close(c2a[1]);
    close(c2a[0]);
    if (read(a2b[0], &n, sizeof(int)) < 0)
    {
      perror("B: Error on reading numbers");
      close(a2b[0]);
      close(b2c[1]);
      free(numbers);
      exit(1);
    }
    if (read(a2b[0], numbers, n * sizeof(int)) < 0)
    {
      perror("B: Error on reading numbers");
      close(a2b[0]);
      close(b2c[1]);
      free(numbers);
      exit(1);
    }
    printf("B: Received %d numbers from A\n", n);
    srand(time(NULL));
    for (int i = 0; i < n; ++i)
      numbers[i] += rand() % 4 + 2;
    if (write(b2c[1], &n, sizeof(int)) < 0)
    {
      perror("B: Error on writing n");
      close(a2b[0]);
      close(b2c[1]);
      free(numbers);
      exit(1);
    }
    if (write(b2c[1], numbers, n * sizeof(int)) < 0)
    {
      perror("B: Error on writing numbers");
      close(a2b[0]);
      close(b2c[1]);
      free(numbers);
      exit(1);
    }
    printf("the numbers are: ");
    for (int i = 0; i < n; ++i)
      printf("%d ", numbers[i]);
    printf("\nB: Sent %d numbers to C\n", n);
    close(a2b[0]);
    close(b2c[1]);
    free(numbers);
    exit(0);
  }
  else
  {
    int f2 = fork();
    if (f2 < 0)
    {
      perror("Error on fork");
      close(a2b[0]);
      close(a2b[1]);
      close(b2c[0]);
      close(b2c[1]);
      close(c2a[0]);
      close(c2a[1]);
      free(numbers);
      exit(1);
    }
    else if (f2 == 0)
    {
      // Process C
      close(a2b[0]);
      close(a2b[1]);
      close(b2c[1]);
      close(c2a[0]);
      if (read(b2c[0], &n, sizeof(int)) < 0)
      {
        perror("C: Error on reading n");
        close(b2c[0]);
        close(c2a[1]);
        free(numbers);
        exit(1);
      }
      if (read(b2c[0], numbers, n * sizeof(int)) < 0)
      {
        perror("C: Error on reading numbers");
        close(b2c[0]);
        close(c2a[1]);
        free(numbers);
        exit(1);
      }
      printf("C: Received %d numbers from B\n", n);
      printf("the numbers are: ");
      int sum = 0;
      for (int i = 0; i < n; i++)
      {
        printf("%d ", numbers[i]);
        sum += numbers[i];
      }
      printf("\n");
      if (write(c2a[1], &sum, sizeof(int)) < 0)
      {
        perror("C: Error on writing sum");
        close(b2c[0]);
        close(c2a[1]);
        free(numbers);
        exit(1);
      }
      printf("C: Sent sum to A\n");
      close(b2c[0]);
      close(c2a[1]);
      free(numbers);
    }
    else
    {
      // Process A
      close(a2b[0]);
      close(b2c[0]);
      close(b2c[1]);
      close(c2a[1]);
      for (int i = 0; i < n; i++)
        scanf("%d", &numbers[i]);
      if (write(a2b[1], &n, sizeof(int)) < 0)
      {
        perror("A: Error on writing n");
        close(a2b[1]);
        close(c2a[1]);
        free(numbers);
        exit(1);
      }
      if (write(a2b[1], numbers, n * sizeof(int)) < 0)
      {
        perror("A: Error on writing numbers");
        close(a2b[1]);
        close(c2a[1]);
        free(numbers);
        exit(1);
      }
      printf("A: Sent %d numbers to B\n", n);
      int sum = 0;
      if (read(c2a[0], &sum, sizeof(int)) < 0)
      {
        perror("A: Error on reading sum from C");
        close(a2b[1]);
        close(c2a[1]);
        free(numbers);
        exit(1);
      }
      printf("A: Received %d sum from C\n", sum);
      close(a2b[1]);
      close(c2a[0]);
      wait(NULL);
      wait(NULL);
      free(numbers);
    }
  }
  return 0;
}