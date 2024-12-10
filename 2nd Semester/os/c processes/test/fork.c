#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	printf("PID: %d\n", getpid());
	int f = fork();
	printf("%d\n", f);
	if (0 == f)
	{
		printf("Baiatu lu tata\n");
		exit(0);
	}
	printf("tatic\n");
	return 0;
}
