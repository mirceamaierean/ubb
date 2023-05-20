
// Write a C program that creates a child process.The parent process will read integers from stand ard input
// After reading each integer N, the parent process will send it via pipe to the child process, which will generate and send back to the parent the first N numbers from the Fibonacci sequence via pipe
// The parent process will read and print the received numbers from the child process
// The parent and child will terminate if the parent reads from standard input a number less than or equal to zero
// The program will perform error checks and handling

// Scrieti un program C care creeaza un proces fiu.Procesul parinte va citi numere intregi de la t astatura
// Dupa fiecare numar intreg N citit, parintele il va trimite prin pipe procesului fiu, care va gen era si va trimite inapoi parintelui prin pipe primele N numere din sirul lui Fibonacci.
// Procesul parinte va citi numerele primite de la procesul fiu si le va afisa pe ecran
// Procesele parinte si fiu isi vor incheia executia cand procesul parinte citeste de la tastatura un numar mai mic sau egal cu zero
// Programul va verifica si va trata aparitia erorilor
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
  int p2c[2], c2p[2], n;
  if (pipe(p2c) < 0 || pipe(c2p))
  {
    perror("pipe error");
    exit(1);
  }
  int f = fork();
  if (f < 0)
  {
    perror("fork error");
    exit(1);
  }
  else if (f == 0)
  {
    // Child process
    close(p2c[1]);
    close(c2p[0]);
    while (1)
    {
      if (read(p2c[0], &n, sizeof(int)) < 0)
      {
        perror("child n error");
        close(p2c[0]);
        close(c2p[1]);
        exit(1);
      }
      if (n == 0)
        break;
      printf("Child received %d\n", n);
      int *send;
      send = (int *)malloc(n * sizeof(int));
      send[0] = 1;
      if (n > 1)
      {
        send[1] = 1;
        for (int i = 2; i < n; ++i)
          send[i] = send[i - 2] + send[i - 1];
      }
      if (write(c2p[1], send, n * sizeof(int)) < 0)
      {
        perror("Error sending array");
        close(p2c[0]);
        close(c2p[1]);
        exit(1);
      }
      printf("Child sent array\n");
      free(send);
    }
    close(p2c[0]);
    close(c2p[1]);
    exit(0);
  }
  else
  {
    close(p2c[0]);
    close(c2p[1]);
    // Parent
    printf("N=");
    scanf("%d", &n);
    while (n > 0)
    {
      int *arr;
      arr = (int *)malloc(n * sizeof(int));
      if (write(p2c[1], &n, sizeof(int)) < 0)
      {
        perror("parent n error");
        close(p2c[1]);
        close(c2p[0]);
        exit(1);
      }
      printf("Parent sent %d\n", n);
      if (read(c2p[0], arr, n * sizeof(int)) < 0)
      {
        perror("parent receive error");
        close(p2c[1]);
        close(c2p[0]);
        exit(1);
      }
      printf("Parent received array\n");
      for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
      printf("\n");
      free(arr);
      printf("N=");
      scanf("%d", &n);
    }
    n = 0;
    if (write(p2c[1], &n, sizeof(int)) < 0)
    {
      perror("error pipe");
      close(p2c[1]);
      close(c2p[0]);
      exit(1);
    }
    close(p2c[1]);
    close(c2p[0]);
    wait(NULL);
  }
  return 0;
}
