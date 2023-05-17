#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>
#include "header.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
  int fd_read = open(myfifo1, O_RDONLY);
  if (fd_read < 0)
  {
    perror("open error on fifo2");
    unlink_fifo();
    exit(1);
  }
  int fd_write = open(myfifo2, O_WRONLY);
  if (fd_write < 0)
  {
    perror("open error on fifo1");
    unlink_fifo();
    exit(1);
  }

  while (1)
  {
    char *str;
    int lung;
    if (read(fd_read, &lung, sizeof(int)) < 0)
    {
      perror("read error");
      unlink_fifo();
      exit(1);
    }
    if (lung == 0)
      break;
    str = malloc(sizeof(char) * (lung + 1));
    memset(str, 0, sizeof(char) * (lung + 1));
    if (read(fd_read, str, sizeof(char) * lung) < 0)
    {
      perror("read error");
      unlink_fifo();
      exit(1);
    }
    printf("B Received: %s\n", str);

    for (int i = 0; i < lung; ++i)
      str[i] = toupper(str[i]);

    if (write(fd_write, str, sizeof(char) * lung) < 0)
    {
      perror("write error");
      unlink_fifo();
      exit(1);
    }

    printf("B Sent: %s\n", str);

    free(str);
  }

  close(fd_read);
  close(fd_write);
  return 0;
}