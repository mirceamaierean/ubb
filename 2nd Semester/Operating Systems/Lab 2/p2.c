/* RO: Copiati acest fisier intr-un alt fisier numit solve.c
 * si rezolvati problemele compilare (erori si warning-uri)si rulare;
 * Programul trebuie sa citeasca trei propozitii de la tastatura si
 * sa creeze apoi un fisier out.txt in care va scrie
 * propozitiile citite inlocuind literele mari cu litere mici,
 * literele mici cu litere mari si va inlocui orice cifra cu succesorul ei,
 * cifra 9 se va inlocui cu 0.
 *
 * EN: Copy this file into a file named solve.c and
 * fix the compilation errors/warnings and the runtime problems;
 * The program will read three sentences from the standard input and then
 * will create a file out.txt in which it will write the sentences
 * replacing lower case letters with upper case letters, upper case
 * letters with lower case letters and any digit will be replaced by its successor,
 * the digit 9 will be replaced with 0.
 *
 * Ex:
 * Compile using:
 * gcc -Wall -g solve.c -o exe
 *
 * Run with:
 * valgrind ./exe
 *
 * Read from standard input:
 * test0123456789
 * another TEST
 * FiNaL_tEsT
 *
 * Expected result:
 * the out.txt file will be created and its contents will be:
 * TEST1234567890
 * ANOTHER test
 * fInAl_TeSt
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int next_digit(char digit)
{
  int tmp = digit - '0';
  tmp = (tmp + 1) % 10;
  return tmp + '0';
}

int main(int argc, char *argv[])
{
  system("leaks p2");
  char *s[3];
  int i, fd, offset;

  for (i = 0; i < 3; i++)
  {
    s[i] = (char *)malloc(20 * sizeof(char));
    // initializes string with 0 (the NULL character)
    memset(s[i], 0, 20 * sizeof(char));
    if (fgets(s[i], 128, stdin) == NULL)
    {
      perror("Error reading the sentence");
      return 1;
    }
  }

  offset = 'a' - 'A';
  for (i = 0; i < 3; i++)
  {
    for (int j = 0; j < strlen(s[i]); j++)
    {
      if (s[i][j] >= 'a' && s[i][j] <= 'z')
      {
        s[i][j] -= offset;
      }
      else if (s[i][j] >= 'A' && s[i][j] <= 'Z')
      {
        s[i][j] += offset;
      }
      else if (s[i][j] >= '0' && s[i][j] <= '9')
      {
        s[i][j] = next_digit(s[i][j]);
      }
    }
  }

  fd = open("out.txt", O_CREAT | O_TRUNC | O_WRONLY);

  if (fd == 0)
  {
    perror("Failed to create the output file");
    return 1;
  }

  for (i = 0; i < 3; i++)
  {
    write(fd, s[i], strlen(s[i]));
  }

  for (i = 0; i < 3; i++)
  {
    free(s[i]);
  }
  return 0;
}
