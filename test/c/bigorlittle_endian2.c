#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	union w
	{
		int a;
		char b;
	} c;
	c.a = 1;
	c.b == 1 ? printf("little endian\n"):printf("big endian\n");
}

