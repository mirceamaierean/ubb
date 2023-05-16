/*
 * Write two C programs that communicate via  FIFO. One program (A) will generate a random number N between 0 and 1000.
 * The other program (B) will try to guess the generated number. B will start by generating a random number between 0 and 1000,
 * and will send it to A which will respond with -1 if the “guess” was lower than N, 1 if the “guess” is greater than N and 0
 * if the guess is correct. B will continuously restrict the guesses based on the responses from A and will stop once it correctly guesses the number.
 * Program A will create and destroy the FIFO.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "header.h"

int main(int argc, char *argv[])
{
  if (0 > mkfifo(myfifo1, 0600))
  {
    perror("Error on make fifo 1");
    exit(1);
  }
  if (0 > mkfifo(myfifo2, 0600))
  {
    perror("Error on make fifo 2");
    exit(1);
  }
  int fd_write = open(myfifo1, O_WRONLY);
  if (-1 == fd_write)
  {
    perror("Error opening fifo 1 in A");
    exit(1);
  }
  int fd_read = open(myfifo2, O_RDONLY);
  if (-1 == fd_read)
  {
    perror("Error opening fifo 2 in A");
    close(fd_write);
    exit(1);
  }
  srandom(getpid());
  int nr = random() % 1001;
  printf("Target is: %d\n", nr);
  int count = 0;
  int not_guessed = 1;
  while (not_guessed)
  {
    int guess;
    if (0 > read(fd_read, &guess, sizeof(int)))
    {
      perror("Error on read from B");
      break;
    }
    count++;
    printf("Received guess: %d\n", guess);
    not_guessed = 0;
    if (guess > nr)
    {
      not_guessed = 1;
    }
    else if (guess < nr)
    {
      not_guessed = -1;
    }
    if (0 > write(fd_write, &not_guessed, sizeof(int)))
    {
      perror("Error on write to B");
      break;
    }
  }
  printf("B guessed correctly in %d attempts.\n", count);

  close(fd_write);
  close(fd_read);
  if (0 > unlink(myfifo1))
  {
    perror("Error removing fifo 1");
  }
  if (0 > unlink(myfifo2))
  {
    perror("Error removing fifo 2");
  }
  return 0;
}