#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <fcntl.h>
#include "header.h"

int main(int argc, char *argv[])
{
  int fd_read = open(myfifo1, O_RDONLY);
  if (fd_read < 0)
  {
    perror("Error opening fifo 2");
    exit(1);
  }

  int fd_write = open(myfifo2, O_WRONLY);
  if (fd_write < 0)
  {
    perror("Error opening fifo 1");
    close(fd_read);
    exit(1);
  }

  srand(getpid());

  int min = 0, max = 1000, stop_sgn = 1, guess = random() % 1000;

  while (stop_sgn)
  {
    if (write(fd_write, &guess, sizeof(int)) < 0)
    {
      perror("Error writing to fifo 1");
      close(fd_read);
      close(fd_write);
      exit(1);
    }
    if (read(fd_read, &stop_sgn, sizeof(int)) < 0)
    {
      perror("Error reading from fifo 2");
      close(fd_read);
      close(fd_write);
      exit(1);
    }
    if (stop_sgn == 1)
      min = guess + 1;
    else if (stop_sgn == -1)
      max = guess - 1;
    sleep(1);
    guess = (min + max) / 2;
  }

  return 0;
}