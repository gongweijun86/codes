#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	char line[128];
	FILE *fpin;
	pid_t pid;	
	char str[256];
	int c;

	if ((fpin = popen("./myuclc", "r")) == NULL)
		printf("fork error\n");
	for (;;)
	{
		fputs("prompt> ", stdout);
		fflush(stdout);
		if (fgets(line, 128, fpin) == NULL)
			break;
		if (fputs(line, stdout) == EOF)
			printf("fputs error\n");
	}
	if (pclose(fpin) == -1)
		printf("pclose error\n");
	putchar('\n');
	exit(0);
}

