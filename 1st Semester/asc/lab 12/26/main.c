#include <stdio.h>
#include <limits.h>

int minim(int, int);

int main()
{
	int min;
	scanf("%d", &min);
	int a = min;
	while (a != -1)
	{
		min = minim(a, min);
		scanf("%d", &a);
	}
	FILE *fout = fopen("minim.txt", "wt");
	fprintf(fout, "%x", min);
	return 0;	
}
