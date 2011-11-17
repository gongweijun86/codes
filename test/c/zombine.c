#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
#define PSCMD "ps -o pid,ppid,state,tty,command"
	pid_t pid;
	if((pid = fork()) < 0)
		printf("fork error");
	else if(pid == 0)
		exit(0);
	sleep(4);
	system(PSCMD);
	exit(0);
}

