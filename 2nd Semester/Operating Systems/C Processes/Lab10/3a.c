// Write 3 C programs (A, B, C). Process A generates a random number X between 100 and 1000 and sends it to process B. Process B multiplies the received number by 2 and sends it to process C. Process C divides the received number by 3 and sends it to process A. Process A increments the number and sends it to process B. This cycle repeats until the number becomes less than 10. Each of the three processes will print a message after receiving a number and before sending a number.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "header.h"

void handle_sigint(int sig)
{
  unlink_fifos();
  exit(0);
}

int main(int argc, char *argv[])
{
  signal(SIGINT, handle_sigint);
  if (mkfifo(myfifo1, 0600) < 0)
  {
    perror("Error creating fifo 1");
    exit(1);
  }
  if (mkfifo(myfifo2, 0600) < 0)
  {
    perror("Error creating fifo 2");
    unlink(myfifo1);
    exit(1);
  }
  if (mkfifo(myfifo3, 0600) < 0)
  {
    perror("Error creating fifo 3");
    unlink(myfifo1);
    unlink(myfifo2);
    exit(1);
  }
  srand(time(NULL));
  int n = rand() % 901 + 100;
  printf("A: %d\n", n);
  int fd_write = open(myfifo1, O_WRONLY);
  if (fd_write < 0)
  {
    perror("Error opening fifo 1");
    unlink_fifos();
    exit(1);
  }
  printf("A opened fifo 1 for writing\n");
  int fd_read = open(myfifo3, O_RDONLY);
  if (fd_read < 0)
  {
    perror("Error opening fifo 3");
    unlink_fifos();
    exit(1);
  }

  if (write(fd_write, &n, sizeof(int)) < 0)
  {
    perror("Error writing to fifo 1");
    unlink_fifos();
    exit(1);
  }
  while (n >= 10)
  {
    if (read(fd_read, &n, sizeof(int)) < 0)
    {
      perror("Error reading from fifo 3");
      unlink_fifos();
      exit(1);
    }
    if (n >= 0)
      printf("A received %d\n", n);
    if (n < 10)
      n = -1;
    if (write(fd_write, &n, sizeof(int)) < 0)
    {
      perror("Error writing to fifo 1");
      unlink_fifos();
      exit(1);
    }
    if (n >= 0)
      printf("A sent %d\n", n);
  }
  close(fd_write);
  close(fd_read);
  unlink_fifos();
  return 0;
}