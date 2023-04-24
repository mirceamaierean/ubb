#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_FILE "sum_fifo"

int main()
{
  int a[] = {1, 2, 3, 4}, f;

  // open FIFO for writing
  f = open(FIFO_FILE, O_WRONLY);

  a[0] += a[1];
  // write partial sum to FIFO
  write(f, &a[0], sizeof(a[0]));

  // close FIFO
  close(f);

  return 0;
}
