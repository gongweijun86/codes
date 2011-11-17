#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
volatile sig_atomic_t quitflag;

static void
sig_int(int signo)
{
	if(signo == SIGINT)
		printf("\ninterupt!\n");
	else if(signo == SIGQUIT)
		quitflag = 1;
}

int
main()
{
	sigset_t newmask, oldmask, zeromask;

	if(signal(SIGINT, sig_int) == SIG_ERR)
		printf("signal(SIGINT) error!");
	if(signal(SIGQUIT, sig_int) == SIG_ERR)
		printf("signal(SIGQUIT) error!");
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);

	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		printf("sIG_BLOCK error!");
	while(quitflag == 0)
	{
		printf("**********************");
		sigsuspend(&zeromask);
	}
	quitflag = 0;
	printf("------------------");
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		printf("SIG_SETMASK error!");
	exit(0);
}
