#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char buf[128];
	pid_t pid;
	int status;

	printf("%% ");
	while(fgets(buf, 128, stdin) != NULL)
	{
		if(buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;
		if((pid = fork()) < 0)
			printf("fork error");
		else if(pid == 0)
		{
			execlp(buf, buf, (char*)0);
			printf("couldn't execute :%s", buf);
			exit(127);
		}
		if((pid = waitpid(pid, &status, 0)) < 0)
			printf("waitpid error");
		printf("%% ");
	}
	exit(0);
}

