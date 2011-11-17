#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

static void sig_pipe(int);


int main(int argc, char* argv[])
{
	int n, fd1[2], fd2[2];
	pid_t pid;
	char line[128];

	if (signal(SIGPIPE, sig_pipe) == SIG_ERR)
		printf("signal error\n");

	if (pipe(fd1) < 0 || pipe(fd2) < 0)
		printf("pipe error\n");

	if ((pid = fork()) < 0)
		printf("fork erronr\n");
	else if(pid > 0)
	{
		close(fd1[0]);
		close(fd2[1]);
		while (fgets(line, 128, stdin) != NULL)
		{
			n = strlen(line);
			if (write(fd1[1], line, n) != n)
				printf("write error\n");
			if ((n = read(fd2[0], line, 128)) < 0)
				printf("read error\n");
			if (n == 0)
			{
				printf("child closed pipe\n");
				break;
			}
			line[n] = 0;
			if (fputs(line, stdout) == EOF)
				printf("fputs error\n");
		}
		if (ferror(stdin))
			printf("fgets error\n");
		exit(0);
	}
	else
	{
		close(fd1[1]);
		close(fd2[0]);
		if (fd1[0] != STDIN_FILENO)
		{
			if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
				printf("dup2 error to stdin");
			close(fd1[0]);
		}
		if (fd2[1] != STDOUT_FILENO)
		{
			if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
				printf("dup2 error to stdout\n");
			close(fd2[1]);
		}
		if (execl("./add2", "add2", (char*)0) < 0)
			printf("execl error\n");
	}
	exit(0);
}

static void sig_pipe(int signo)
{
	printf("SIGPIPE caught\n");
	exit(1);
}

