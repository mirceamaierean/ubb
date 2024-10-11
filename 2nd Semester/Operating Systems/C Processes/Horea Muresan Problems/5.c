#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

// self-explanatory function name
// functie cu nume sugestiv
int contains_7_or_is_multiple_of_7(int nr)
{
  if (nr % 7 == 0)
  {
    return 1;
  }
  while (nr > 0)
  {
    if (nr % 10 == 7)
    {
      return 1;
    }
    nr = nr / 10;
  }
  return 0;
}

// Definim o functie care va gestiona atat crearea de noi procese cat si partea de joc;
// -- Partea de joc poate fi extrasa intr-o alta functie pentru o mai buna organizare a codului;
// Pasam functiei un sir de pipes, un index si numarul N
// index va fi folosit atat ca o variabila prin care controlam cate procese sunt create, cat si ca un ID
// pentru fiecare proces, pentru a putea identifica cu care pipe(s) va interactiona
//
// Define a function that will manage both child process creation as well as playing the game;
// -- The game playing could be extracted in its own function for a cleaner code;
// We pass to the function an array of pipes, an index and the number N
// index will serve as a way to limit the number of processes to be created, as well as an ID
// for each process, to determine with which pipe(s) it will interact
void fork_and_communicate(int pipes[][2], int index, int n)
{
  // verificam daca mai putem crea inca un proces
  // check if we can create one more process
  if (index + 1 < n)
  {
    // daca da, incercam sa cream inca un proces
    // if yes, try to create one more process
    int f = fork();
    if (0 > f)
    {
      // oh no, an error
      perror("Error on creating child");
      return;
    }
    else if (0 == f)
    {
      // procesul fiu este responsabil sa apeleze recursiv functia,
      // incrementand parametrul index ca sa contorizam cate procese au fost create
      // the child process must call recursively the function,
      // incrementing the index parameter so we can keep track of how many processes were created
      fork_and_communicate(pipes, index + 1, n);
      return;
    }
  }
  // indiferent daca procesul curent trebuie sa creeze un proces nou sau nu, trebuie sa participe la joc
  // regardless if the current process must create a new process, if definitely has to play the game
  int nr = 1, i;
  // folosim index pe post de ID in proces
  // use index as an ID in the process

  // impunem ca un proces sa citeasca din pipes[index][0] si sa scrie in pipes[index+1][1]
  // impose that a process reads from pipes[index][0] and writes to pipes[index+1][1]
  int read_idx = index % n;
  // modulo n trateaza cazul ultimului proces, cu index == n - 1, care trebuie sa comunice cu procesul initial, cu index == 0
  // modulo n handles the case of the last process, where index == n - 1, which must communicate with the original process, where index == 0
  int write_idx = (index + 1) % n;
  // inchidem toate canalele de comunicare cu exceptia pipes[index][0], pipes[index+1][1]
  // close all pipes except pipes[index][0], pipes[index+1][1]
  for (i = 0; i < n; i++)
  {
    if (i == read_idx)
    {
      close(pipes[i][1]);
    }
    else if (i == write_idx)
    {
      close(pipes[i][0]);
    }
    else
    {
      close(pipes[i][0]);
      close(pipes[i][1]);
    }
  }
  // consideram ca procesul original porneste jocul
  // consider that the initial process starts the game
  if (index == 0)
  {
    printf("%d - start\n", nr);
    if (0 > write(pipes[write_idx][1], &nr, sizeof(int)))
      perror("Error on writing number");
  }
  // fiecare proces joaca pana cand conditia de esuare se indeplineste
  // each process plays until the fail condition is met
  while (nr >= 1)
  {
    if (0 > read(pipes[read_idx][0], &nr, sizeof(int)))
      perror("Error on reading number");
    // jocul porneste de la 1, consideram ca daca numarul este egal cu 0, trebuie sa incheiem
    // the game starts from 1, consider that if the number is equal to 0, we should stop
    if (nr != 0)
    {
      nr++;
      // alegem un numar random dintre 0, 1, 2
      // pick a random number from 0, 1, 2
      int success = random() % 3;
      // verificam daca avem conditie de boltz
      // check if the boltz condition is true
      if (contains_7_or_is_multiple_of_7(nr))
      {
        // daca da, verificam rezultatul de la random, daca este 0 -> procesul va "gresi" si jocul se incheie
        // if yes, we check the result from random, if it is 0 -> the process will make a "mistake" and the game ends
        if (!success)
        {
          printf("%d - fail\n", nr);
          nr = 0;
        }
        else
        {
          printf("Boltz!\n");
        }
      }
      else
      {
        printf("%d\n", nr);
      }

      if (0 > write(pipes[write_idx][1], &nr, sizeof(int)))
      {
        perror("Error on writing number");
      }
    }
    else
    {
      // in caz de incheiere, procesul curent este singurul care are un canal de comunicare deschis cu procesul index + 1, deci este responsabil de propagarea mesajului de stop
      // if it is time to close, the current process is the only one that has an open pipe to process index + 1, so it is responsible of propagating the stop message
      if (0 > write(pipes[write_idx][1], &nr, sizeof(int)))
      {
        perror("Error on writing number");
      }
      break;
    }
  }
  wait(0);
  // inchidem restul de canale
  // close the rest of the pipes
  close(pipes[read_idx][0]);
  close(pipes[write_idx][1]);
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Provide an integer argument!\n");
    exit(1);
  }
  int n = atoi(argv[1]), i;
  // folosim un sir de pipes, fiecare pereche de pipes consecutive ar trebui sa asigure ca un proces poate citi numarul si poate sa scrie numarul
  // use an array of pipes, each pair of consecutive pipes should ensure that a process can read the number and can write the number
  int pipes[n][2];
  for (i = 0; i < n; i++)
  {
    if (0 > pipe(pipes[i]))
    {
      perror("Error on opening pipe");
      exit(1);
    }
  }
  srandom(time(NULL));
  fork_and_communicate(pipes, 0, n);
  return 0;
}