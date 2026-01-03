#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fa, fb, k;
    char s[32];
    if (fork() == 0)
    {
        fa = open("fa", O_WRONLY);
        for (k = 1; k < argc; k++)
        {
            write(fa, argv[k], strlen(argv[k]));
            write(fa, "\n", 1);
        }
        close(fa);
        exit(0);
    }
    if (fork() == 0)
    {
        execlp("bash", "bash", "-c", "sort <fa >>fb", NULL);
        exit(0);
    }

    if (fork() == 0)
    {
        int cnt = 0;
        fb = open("fb", O_RDONLY);
        while ((k = read(fb, s, 1)) > 0)
        {
            ++cnt;
            write(2, s, k);
        }
        close(fb);
        exit(0);
    }
    wait(NULL);
    wait(NULL);
    wait(NULL);
    return 0;
}