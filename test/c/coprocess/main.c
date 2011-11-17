#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static void
sig_pipe(int signo)
{
	printf("SIGPIPE caught!");
	exit(1);
}


int
main()
{
	int n, fd1[2], fd2[2];
	pid_t pid;
	char line[128];

	if(signal(SIGPIPE, sig_pipe) == SIG_ERR)
		printf("signal error!");
	if(pipe(fd1) < 0 || pipe(fd2) < 0)
		printf("pipe error!");
	if((pid = fork()) < 0)
	{
		printf("fork error!");
	}
	else if(pid > 0){
		close(fd1[0]);
		close(fd2[1]);
		sleep(5);
		printf("parent\n");
		while(fgets(line, 128, stdin) != NULL)
		{
			n = strlen(line);
			if(write(fd1[1], line, n) != n)
				printf("write error to pipe!");
			if((n = read(fd2[0], line, 128)) < 0)
				printf("read error from pipe!");
			if(n ==0)
			{
				printf("child closed pipe!");
				break;
			}
			line[n] = 0;
			if(fputs(line, stdout) == EOF)
				printf("fputs error");
		}
		if(ferror(stdin))
			printf("fgets error on stdin!");
		exit(0);
	}
	else{
		close(fd1[1]);
		close(fd2[0]);
		printf("child1!\n");
		fflush(stdout);
		if(fd1[0] != STDIN_FILENO)
		{
			if(dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
				printf("dup2 error!");
			close(fd1[0]);
		}
		printf("childchild!\n");
		printf("childchild!\n");
		printf("childchild!\n");
		printf("childchild!\n");
		printf("childchild!\n");
		if(fd2[1] != STDOUT_FILENO)
		{
			if(dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
				printf("dup2 error!");
			close(fd2[1]);
		printf("childchild!-----------\n");
		}
		printf("child2!\n");
		fflush(stdout);
		if(execl("./add2", "add2", (char *)0) < 0)
			printf("execl error!");
		printf("child3!\n");
		fflush(stdout);
	}
	exit(0);
}
