#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	printf("real uid = %d, effective uid = %d\n", getuid(), geteuid());
	exit(0);
}

