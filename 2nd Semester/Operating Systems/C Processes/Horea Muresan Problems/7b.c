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
  int fd_read = open(myfifo1, O_RDONLY);

  if (fd_read < 0)
  {
    perror("open error on fifo1");
    exit(1);
  }

  int fd_write = open(myfifo2, O_WRONLY);
  if (fd_write < 0)
  {
    perror("open error on fifo2");
    exit(1);
  }

  int n = 100;
  while (n != 10)
  {
    if (read(fd_read, &n, sizeof(int)) < 0)
    {
      perror("read");
      unlink_fifo();
      exit(1);
    }
    printf("B received %d\n", n);
    if (n != 10)
    {
      n = rand() % 10 + 1;
      if (write(fd_write, &n, sizeof(int)) < 0)
      {
        perror("write");
        unlink_fifo();
        exit(1);
      }
      printf("B sent %d\n", n);
    }
  }

  close(fd_read);
  close(fd_write);
  return 0;
}