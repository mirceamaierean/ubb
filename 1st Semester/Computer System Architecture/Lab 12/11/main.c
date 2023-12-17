#include <stdio.h>

int base10(char sir[]);

int main()
{
	char sir[65];
	while (1)
    {
		scanf("%s", sir);
		int a = base10(sir);
		printf("%x\n", a);
	}
    return 0;
}

