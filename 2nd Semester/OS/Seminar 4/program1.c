#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_FILE "sum_fifo"

int main()
{
  int a[] = {1, 2, 3, 4}, f;

  // create FIFO if it doesn't exist
  mkfifo(FIFO_FILE, 0666);

  // open FIFO for reading
  f = open(FIFO_FILE, O_RDONLY);

  a[2] += a[3];

  // read partial sum from FIFO
  read(f, &a[0], sizeof(a[0]));

  a[0] += a[2];

  // close FIFO
  close(f);

  // print final sum
  printf("Final sum: %d\n", a[0]);

  return 0;
}
