#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

void
pr_mask(const char* str)
{
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	if(sigprocmask(0, NULL, &sigset) < 0)
		printf("sigprocmask error");
	printf("%s\n",str);

	if(sigismember(&sigset, SIGINT)) printf("SIGINT ");
	if(sigismember(&sigset, SIGQUIT)) printf("SIGQUIT ");
	if(sigismember(&sigset, SIGUSR1)) printf("SIGUSR1 ");
	if(sigismember(&sigset, SIGALRM)) printf("SIGALRM ");
	if(sigismember(&sigset, SIGKILL)) printf("SIGKILL ");

	printf("\n");
	errno = errno_save;
}

int main(int argc, char* argv[])
{
	sigset_t sigset;
	sigprocmask(0, NULL, &sigset);

	sigaddset(&sigset, SIGINT);
	sigprocmask(SIG_SETMASK, &sigset, NULL);

	pr_mask("hello\n");
	exit(0);
}

