#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int i;
	int *a = (int*)malloc(sizeof(int) * (argc - 1));
//	printf("%d\n",argc);
	for (i = 1; i < argc; i++)
	{
		a[i - 1] = atoi(argv[i]);
	}
	int max;
	max = a[0];
	int num = 0;
	for (i = 0; i < argc - 2; i++)
	{
		if (max < a[i + 1])
		{
			num++;
			max = a[i + 1];
		}
	}
	printf("%d\n", num);

	free(a);
	exit(0);
}

