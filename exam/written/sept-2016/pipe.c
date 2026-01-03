#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    int pfd[2], i, n = 10;
    pipe(pfd);
    for (i = 0; i < 3; i++)
    {
        if (fork() == 0)
        {
            int descriptor = write(pfd[1], &i, sizeof(int));
            printf("%d %d %d\n", getpid(), descriptor, i);
            close(pfd[0]);
            close(pfd[1]);
        }
        else
        {
            exit(0);
            // see questions c) and d)
        }
    }
    for (i = 0; i < 3; i++)
    {
        wait(0);
        int descriptor = read(pfd[0], &n, sizeof(int));
        printf("%d %d aici\n", n, descriptor);
    }
    close(pfd[0]);
    close(pfd[1]);
    return 0;
}