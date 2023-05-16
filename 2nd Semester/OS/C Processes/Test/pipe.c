/*
Pipe Steps:
1) Declaratia unui array de int-uri de dimensiune 2 (0 citire, 1 scriere)
2) Apelul functiei pipe() care va crea un pipe si va returna 0 in caz de succes
3) Close fd[0] si fd[1] in procesul copil si parinte respectiv
4) Daca vrem sa redirectam stdout-ul procesului copil in pipe, atunci trebuie sa facem un duplicat al descriptorului de fisiere al stdout-ului (dup(1))
5) Apelul functiei dup2() care va face ca stdout-ul procesului copil sa fie redirectat in pipe
6) Pentru a scrie in pipe, avem write(fd[1], referinta la buffer, dimensiunea buffer-ului)
7) Pentru a citi din pipe, avem read(fd[0], referinta la buffer, dimensiunea buffer-ului)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

  int fd[2];
  pipe(fd);
  if (fork() == 0)
  {
    close(fd[0]);
    printf("Sunt copilul cu PID-ul %d\n", getpid());
    char message[100];
    printf("Introduceti un mesaj: ");
    fgets(message, 100, stdin);
    write(fd[1], message, strlen(message) + 1);
    exit(0);
  }

  close(fd[1]);
  printf("Sunt parintele cu PID-ul %d\n", getpid());
  char buf[100];
  read(fd[0], buf, 100);
  printf("Am citit din pipe: %s\n", buf);
  printf("argc: %d\n", argc);
  execvp(argv[1], argv + 1);
  return 0;
}