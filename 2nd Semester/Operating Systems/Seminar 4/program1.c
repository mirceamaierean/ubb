/*
FIFO STEPS
1) Creeaza FIFO: mkfifo(FIFO_FILE, 0600)
2) Deschide FIFO pentru scriere: open(FIFO_FILE, O_WRONLY), sau pentru citire: open(FIFO_FILE, O_RDONLY)
3) Pentru a scrie in FIFO: write(f, adresa, nr_octeti)
4) Pentru a citi din FIFO: read(f, adresa, nr_octeti)
5) Pentru a inchide FIFO: close(f)
6) Pentru a sterge FIFO: unlink(FIFO_FILE)
*/

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
  if (mkfifo(FIFO_FILE, 0600) < 0)
  {
    printf("Error creating FIFO\n");
    return 1;
  }

  // open FIFO for reading
  f = open(FIFO_FILE, O_RDONLY);

  if (f < 0)
  {
    printf("Error opening FIFO\n");
    return 1;
  }

  // read partial sum from FIFO
  read(f, a, 4 * sizeof(int));

  // close FIFO
  close(f);
  unlink(FIFO_FILE);
  // print final sum
  for (int i = 0; i < 4; ++i)
    printf("%d ", a[i]);

  return 0;
}
