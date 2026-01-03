#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void f(char *a, char *b, int w, char *s)
{
    int f[2], r = 1 - w;
    char c;

    if (fork() == 0)
    {
        f[0] = open(a, w == 0 ? O_WRONLY : O_RDONLY);
        f[1] = open(b, w == 1 ? O_WRONLY : O_RDONLY);
        write(f[w], s, 1);
        read(f[r], &c, 1);
        printf("%c\n", c);
        close(f[0]);
        close(f[1]);
        exit(0);
    }
}
int main(int n, char **a)
{
    int i;
    for (i = 1; i < n; i += 4)
    {
        f(a[i], a[i + 1], a[i + 2][0] - '0', a[i + 3]);
    }
    for (i = 1; i < n; i += 4)
    {
        wait(0);
    }
    return 0;
}