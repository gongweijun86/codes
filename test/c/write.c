#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	char buf[] = "helloworld\n";
	if(write(STDOUT_FILENO, buf, sizeof(buf) -1) != sizeof(buf) -1)
		printf("error!");
}

