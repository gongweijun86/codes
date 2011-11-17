#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int globe = 6;

int main(int argc, char* argv[])
{
	int var;
	pid_t pid;

	var = 88;
	printf("before vfrok\n");
	if((pid = vfork()) < 0)
		printf("vfork error");
	else if(pid == 0)
	{
		globe++;
		var++;
		exit(0);
	}
	
	int j = dup(STDOUT_FILENO);

	fclose(stdout);
	int i;
	i = printf("pid = %d, globe = %d, var = %d,\n",getpid(), globe, var);
	char buf[16];
	sprintf(buf, "%d\n", i);
	write(j , buf, strlen(buf));
	exit(0);
}

