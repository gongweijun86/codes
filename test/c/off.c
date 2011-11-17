#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
	{
		printf("cannot seek!");
	}
	else{
		printf("seek ok!");
	}
	exit(0);
}

