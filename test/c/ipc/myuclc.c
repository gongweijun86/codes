#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
	int c;
	while((c = getchar()) != EOF)
	{
		if (isupper(c))
			c = tolower(c);
		if (putchar(c) == EOF)
			printf("ouput error!\n");
		if (c == '\n')
			fflush(stdout);
	}
	exit(0);
}

