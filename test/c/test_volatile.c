#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	volatile long i;
	for(i = 0; i < 100000000; i++);
}

