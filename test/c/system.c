#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int status;

	if(argc < 2)
		printf("argument wrong!");
	if((status = system(argv[1])) < 0)
		printf("system error!");
	printf("status: %d\n", status);
	exit(0);
}

