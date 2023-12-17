#include <stdio.h>
#include <stdlib.h>

void printMatrix(int **m, int rows, int cols, char name)
{
  int i, j;
  printf("Matrix %c:\n", name);
  for (i = 0; i < rows; i++)
  {
    for (j = 0; j < cols; j++)
    {
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }
}

void printArray(int *a, int len, char name)
{
  int i;
  printf("Array %c:\n", name);
  for (i = 0; i < len; i++)
  {
    printf("%d ", a[i]);
  }
  printf("\n");
}

void sum(int **x, int *y, int rows, int cols)
{
  int i, j;
  for (i = 0; i < cols; i++)
  {
    y[i] = 0;
    for (j = 0; j < rows; j++)
    {
      y[i] += x[j][i];
    }
  }
}

int main(int argc, char **argv)
{
  system("leaks p1");
  int **x, i, j, rows, cols;
  FILE *f;

  if (argc != 2)
  {
    printf("Please provide one filename\n");
    exit(0);
  }
	
  f = fopen(argv[1], "r");

  fscanf(f, "%d%d", &rows, &cols);

  x = (int**)malloc(sizeof(int*) * rows);

  for (i = 0; i <= rows; i++)
  {
    x[i] = malloc(sizeof(int) * cols);
  }
  for (i = 0; i < rows; i++)
  {
    for (j = 0; j < cols; j++)
    {
      fscanf(f, "%d", &x[i][j]);
    }
  }

  fclose(f);

  printMatrix(x, rows, cols, 'x');

  int *y = (int*)malloc(sizeof(int) * cols);
  sum(x, y, rows, cols);
  printArray(y, cols, 'y');

  for (i = 0; i < rows; i++)
    free(x[i]);

  free(x);
  free(y);

  return 0;
}
