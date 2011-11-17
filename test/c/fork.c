#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	char line[128];
	char line1[128];
	if((pid = fork()) < 0)
	{
		printf("fork error!");
	}
	else if(pid == 0)
	{
		int i;
		while(fgets(line, 128, stdin))
		{
			printf("child!\n");
			fflush(stdout);
			
		}
		exit(0);
	}
	else{
		while(fgets(line1, 128, stdin))
		{
			printf("parent!\n");
			fflush(stdout);
		}
	}
	exit(0);
}
