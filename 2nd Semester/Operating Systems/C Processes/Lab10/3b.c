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

int main(int argc, char *argv[])
{
  printf("B opened fifo 2 for writing\n");
  int fd_read = open(myfifo1, O_RDONLY);
  if (fd_read < 0)
  {
    perror("Error opening fifo 1");
    unlink_fifos();
    exit(1);
  }
  int fd_write = open(myfifo2, O_WRONLY);
  if (fd_write < 0)
  {
    perror("Error opening fifo 2");
    unlink_fifos();
    exit(1);
  }
  srand(time(NULL));
  int n = 10;
  while (n >= 0)
  {
    if (read(fd_read, &n, sizeof(int)) < 0)
    {
      perror("Error reading from fifo 1");
      unlink_fifos();
      exit(1);
    }
    if (n >= 0)
      printf("B received %d\n", n);
    n *= 2;
    if (write(fd_write, &n, sizeof(int)) < 0)
    {
      perror("Error writing to fifo 2");
      unlink_fifos();
      exit(1);
    }
    if (n >= 0)
      printf("B sent %d\n", n);
  }
  close(fd_write);
  close(fd_read);
  return 0;
}