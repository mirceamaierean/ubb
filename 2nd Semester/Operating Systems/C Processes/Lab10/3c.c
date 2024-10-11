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
  int fd_read = open(myfifo2, O_RDONLY);
  if (fd_read < 0)
  {
    perror("Error opening fifo 2");
    unlink_fifos();
    exit(1);
  }
  int fd_write = open(myfifo3, O_WRONLY);
  printf("C opened fifo 3 for writing\n");
  if (fd_write < 0)
  {
    perror("Error opening fifo 3");
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
      printf("C received %d\n", n);
    n /= 3;
    if (write(fd_write, &n, sizeof(int)) < 0)
    {
      perror("Error writing to fifo 2");
      unlink_fifos();
      exit(1);
    }
    if (n >= 0)
      printf("C sent %d\n", n);
  }
  close(fd_write);
  close(fd_read);
  return 0;
}