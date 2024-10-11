#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_FILE "sum_fifo"

int main()
{
  int a[] = {5, 6, 7, 8}, f;

  // open FIFO for writing
  f = open(FIFO_FILE, O_WRONLY);
  // write partial sum to FIFO
  write(f, a, 4 * sizeof(int));

  // close FIFO
  close(f);

  return 0;
}
