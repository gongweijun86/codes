#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int i;
	for(;;)	
	{
		for(i = 0; i < 9600000; i++);
		sleep(10);
	}
	exit(0);
}

