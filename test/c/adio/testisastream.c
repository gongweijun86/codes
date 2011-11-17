#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int i,fd;
	for(i = 0; i < argc; i++)
	{
		if((fd = open(argv[i], O_RDONLY)) < 0)
		{
			printf("%s cannot open ",argv[i]);
			continue;
		}
		if(isastream(fd) == 0)
			printf("%s: not a stream\n",argv[i]);
		else
			printf("%s is a stream device\n",argv[i]);
	}
	exit(0);
}

