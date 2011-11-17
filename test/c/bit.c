#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int a = 0x1234;
	int b = a >>> 4;
	printf("b : %d\n", b);
}

