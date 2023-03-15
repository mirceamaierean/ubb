/*
  2  * RO: Copiati acest fisier intr-un alt fisier numit solve.c
  3  * si rezolvati problemele compilare (erori si warning-uri) si rulare;
  4  * Programul trebuie sa citeasca 2 matrici cu aceleasi dimensiuni dintr-un
  5  * fisier dat ca argument la linia de comanda si sa calculeze diferenta matricilor.
  6
  7  *
  8  * EN: Copy this file into a file named solve.c and
  9  * fix the compilation errors/warnings and the runtime problems;
 10  * The program will read 2 matrices of equal dimensions from a file provided from
 11  * the command line, and then will calculate their difference.
 12  * Ex:
 13  *
 14  * Place the following 5 lines in a file named in.txt:
 15     2 4
 16     1 2 3 4
 17     10 11 12 13
 18     10 11 12 13
 19     10  9  7  3
 20  * Compile using:
 21  * gcc -Wall -g solve.c -o exe
 22  *
 23  * Run with:
 24  * valgrind ./exe in.txt
 25  *
 26  * Rezultat/Result:
 27  * The program will print the two matrixes it read and will also print the difference:
 28     -9 -9 -9 -9
 29      0 2 5 10
 30  */
#include <stdio.h>
#include <stdlib.h>

void printMatrix(int **m, int rows, int cols, char *name)
{
  int i, j;
  printf("Matrix %s:\n", name);
  for (i = 0; i < rows; i++)
  {
    for (j = 0; j < cols; j++)
    {
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }
}

void sub(int **x, int **y, int **z, int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++)
  {
    for (j = 0; j < cols; j++)
      z[i][j] = x[i][j] - y[i][j];
  }
}

int main(int argc, char **argv)
{
  int **x, **y, rows, cols;
  FILE *f;
  if (argc != 2)
  {
    printf("Please provide one filename\n");
    exit(0);
  }
  f = fopen(argv[1], "r");
  fscanf(f, "%d%d", &rows, &cols);
  x = (int **)malloc(sizeof(int *) * rows);
  y = (int **)malloc(sizeof(int *) * rows);
  int i, j;
  for (i = 0; i < rows; i++)
  {
    x[i] = (int *)malloc(sizeof(int) * cols);
    y[i] = (int *)malloc(sizeof(int) * cols);
  }
  for (i = 0; i < rows; i++)
  {
    for (j = 0; j < cols; j++)
    {
      fscanf(f, "%d", &x[i][j]);
    }
  }
  for (i = 0; i < rows; i++)
  {
    for (j = 0; j < cols; j++)
    {
      fscanf(f, "%d", &y[i][j]);
    }
  }
  fclose(f);
  printMatrix(x, rows, cols, "x");
  printMatrix(y, rows, cols, "y");

  int **z;
  z = (int **)malloc(sizeof(int *) * rows);

  for (i = 0; i < rows; i++)
    z[i] = (int *)malloc(sizeof(int) * cols);

  sub(x, y, z, rows, cols);
  printMatrix(z, rows, cols, "x-y");
  for (i = 0; i < rows; i++)
  {
    free(x[i]);
    free(y[i]);
    free(z[i]);
  }
  free(x);
  free(y);
  free(z);
  return 0;
}
