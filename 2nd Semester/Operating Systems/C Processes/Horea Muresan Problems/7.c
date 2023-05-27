/*
 * Write a C program that creates two child processes. The two child processes will
 * alternate sending random integers between 1 and 10(inclusively) to one another
 * until one of them sends the number 10. Print messages as the numbers are sent.
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  int c1_to_c2[2], c2_to_c1[2];
  if (pipe(c1_to_c2) < 0)
  {
    perror("Error on pipe 1 ");
    exit(1);
  }
  if (pipe(c2_to_c1) < 0)
  {
    perror("Error on pipe 2 ");
    exit(1);
  }
  int f1 = fork();
  if (f1 < 0)
  {
    perror("Error on fork 1 ");
    close(c1_to_c2[0]);
    close(c1_to_c2[1]);
    close(c2_to_c1[0]);
    close(c2_to_c1[1]);
    exit(1);
  }
  if (f1 == 0)
  {
    close(c1_to_c2[0]);
    close(c2_to_c1[1]);
    int n;
    srandom(getpid());
    if (read(c2_to_c1[0], &n, sizeof(int)) < 0)
    {
      perror("Error on read from child 2 ");
      close(c1_to_c2[1]);
      close(c2_to_c1[0]);
      exit(1);
    }
    printf("Child 1 received %d from child 2\n", n);
    while (n != 10)
    {
      n = random() % 10 + 1;
      if (write(c1_to_c2[1], &n, sizeof(int)) < 0)
      {
        perror("Error on write to child 2 ");
        close(c1_to_c2[1]);
        close(c2_to_c1[0]);
        exit(1);
      }
      if (n == 10)
        break;
      if (read(c2_to_c1[0], &n, sizeof(int)) < 0)
      {
        perror("Error on read from child 2 ");
        close(c1_to_c2[1]);
        close(c2_to_c1[0]);
        exit(1);
      }
      printf("Child 1 read %d\n", n);
    }
    close(c1_to_c2[1]);
    close(c2_to_c1[0]);
    exit(0);
  }

  int f2 = fork();
  if (f2 < 0)
  {
    perror("Error on fork 2 ");
    close(c1_to_c2[0]);
    close(c1_to_c2[1]);
    close(c2_to_c1[0]);
    close(c2_to_c1[1]);
    exit(1);
  }
  if (f2 == 0)
  {
    close(c1_to_c2[1]);
    close(c2_to_c1[0]);
    int n;
    srandom(getpid());
    n = random() % 10 + 1;
    if (write(c2_to_c1[1], &n, sizeof(int)) < 0)
    {
      perror("Error on write to child 1 ");
      close(c1_to_c2[0]);
      close(c2_to_c1[1]);
      exit(1);
    }
    printf("Child 2 sent %d to child 1\n", n);
    while (n != 10)
    {
      if (read(c1_to_c2[0], &n, sizeof(int)) < 0)
      {
        perror("Error on read from child 1 ");
        close(c1_to_c2[0]);
        close(c2_to_c1[1]);
        exit(1);
      }
      printf("Child 2 read %d\n", n);
      if (n == 10)
        break;
      n = random() % 10 + 1;
      if (write(c2_to_c1[1], &n, sizeof(int)) < 0)
      {
        perror("Error on write to child 1 ");
        close(c1_to_c2[0]);
        close(c2_to_c1[1]);
        exit(1);
      }
    }
    close(c1_to_c2[0]);
    close(c2_to_c1[1]);
    exit(0);
  }
  wait(0);
  wait(0);
  return 0;
}
