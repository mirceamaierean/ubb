// Write 2 C programs, A and B. A receives however many command line arguments and sends them to process B. Process B converts all lowercase letters from the received arguments to uppercase arguments and sends the results back to A. A reads the results, concatenates them and prints.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>
#include "header.h"
#include <fcntl.h>

void handler(int sign)
{
  unlink_fifo();
  exit(0);
}

int main(int argc, char *argv[])
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
    unlink_fifo();
    exit(1);
  }
  int fd_read = open(myfifo2, O_RDONLY);
  if (fd_read < 0)
  {
    perror("open error on fifo2");
    unlink_fifo();
    exit(1);
  }

  char *str;
  int len = 0;

  for (int i = 1; i < argc; ++i)
    len += strlen(argv[i]);

  str = malloc(sizeof(char) * (len + 1));
  memset(str, 0, sizeof(char) * (len + 1));

  for (int i = 1; i < argc; ++i)
  {
    int lung = strlen(argv[i]);
    char *buff = malloc(sizeof(char) * (lung + 1));
    memset(buff, 0, sizeof(char) * (lung + 1));
    if (write(fd_write, &lung, sizeof(int)) < 0)
    {
      perror("write");
      unlink_fifo();
      exit(1);
    }
    if (write(fd_write, argv[i], lung * sizeof(char)) < 0)
    {
      perror("write");
      unlink_fifo();
      exit(1);
    }
    printf("A sent %s with length %d\n", argv[i], lung);
    if (read(fd_read, buff, sizeof(char) * (lung + 1)) < 0)
    {
      perror("read");
      unlink_fifo();
      exit(1);
    }
    printf("A received %s with length %d\n", buff, lung);
    strcat(str, buff);
    free(buff);
  }

  len = 0;
  if (write(fd_write, &len, sizeof(int)) < 0)
  {
    perror("write");
    unlink_fifo();
    exit(1);
  }

  printf("A received %s\n", str);

  close(fd_write);
  close(fd_read);
  unlink_fifo();
  return 0;
}