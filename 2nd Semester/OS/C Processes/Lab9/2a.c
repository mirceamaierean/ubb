/*
 * Write two C programs that communicate via  FIFO. One program (A) will generate a random number N between 0 and 1000.
 * The other program (B) will try to guess the generated number. B will start by generating a random number between 0 and 1000,
 * and will send it to A which will respond with -1 if the “guess” was lower than N, 1 if the “guess” is greater than N and 0
 * if the guess is correct. B will continuously restrict the guesses based on the responses from A and will stop once it correctly guesses the number.
 * Program A will create and destroy the FIFO.
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <math.h>
#include "header.h"

int main(int argc, char *argv[])
{
  if (mkfifo(myfifo1, 0600) < 0)
  {
    perror("Error creating fifo 1");
    exit(1);
  }
  if (mkfifo(myfifo2, 0600) < 0)
  {
    perror("Error creating fifo 2");
    exit(1);
  }

  int fd_write = open(myfifo1, O_WRONLY);
  if (fd_write < 0)
  {
    perror("Error opening fifo 1");
    exit(1);
  }

  int fd_read = open(myfifo2, O_RDONLY);
  if (fd_read < 0)
  {
    perror("Error opening fifo 2");
    close(fd_write);
    exit(1);
  }
  srandom(getpid());
  int n = random() % 1000, guess = 10002;
  printf("Number: %d\n", n);
  while (n != guess)
  {
    if (read(fd_read, &guess, sizeof(int)) < 0)
    {
      perror("Error reading from fifo 2");
      close(fd_read);
      close(fd_write);
      exit(1);
    }
    printf("Guess: %d\n", guess);
    int sent_sgn = 0;
    if (guess > n)
      sent_sgn = -1;
    else if (guess < n)
      sent_sgn = 1;
    if (write(fd_write, &sent_sgn, sizeof(int)) < 0)
    {
      perror("Error writing to fifo 1");
      close(fd_read);
      close(fd_write);
      exit(1);
    }
  }
  close(fd_read);
  close(fd_write);
  if (unlink(myfifo1) < 0)
  {
    perror("Error unlinking fifo 1");
    exit(1);
  }
  if (unlink(myfifo2) < 0)
  {
    perror("Error unlinking fifo 2");
    exit(1);
  }
  return 0;
}