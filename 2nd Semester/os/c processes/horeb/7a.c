// Write two C programs that communicate via fifo. The two processes will alternate sending random integers between 1 and 10 (inclusively) to one another until one of them sends the number 10. Print messages as the numbers are sent. One of the two processes must be responsible for creating and deleting the fifos.
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>
#include "header.h"

void handler(int signo)
{
  unlink_fifo();
  exit(0);
}

int main()
{
  signal(SIGINT, handler);
  if (mkfifo(myfifo1, 0600) < 0)
  {
    perror("mkfifo");
    exit(1);
  }
  if (mkfifo(myfifo2, 0600) < 0)
  {
    perror("mkfifo");
    exit(1);
  }
  int fd_write = open(myfifo1, O_WRONLY);

  if (fd_write < 0)
  {
    perror("open error on fifo1");
    exit(1);
  }

  int fd_read = open(myfifo2, O_RDONLY);
  if (fd_read < 0)
  {
    perror("open error on fifo2");
    unlink_fifo();
    exit(1);
  }

  srand(time(NULL));

  int n = rand() % 10 + 1;
  if (write(fd_write, &n, sizeof(int)) < 0)
  {
    perror("write");
    unlink_fifo();
    exit(1);
  }

  printf("A sent %d\n", n);

  while (n != 10)
  {
    if (read(fd_read, &n, sizeof(int)) < 0)
    {
      perror("read");
      unlink_fifo();
      exit(1);
    }
    printf("A received %d\n", n);
    if (n != 10)
    {
      n = rand() % 10 + 1;
      if (write(fd_write, &n, sizeof(int)) < 0)
      {
        perror("write");
        unlink_fifo();
        exit(1);
      }
      printf("A sent %d\n", n);
    }
  }

  close(fd_read);
  close(fd_write);
  unlink_fifo();

  return 0;
}
