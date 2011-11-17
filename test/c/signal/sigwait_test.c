#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>

void sig_handler(int signum)
{
	printf("receive signal: %d\n",signum);
}

void* sigmgr_thread()
{
	sigset_t waitset, oset;
	int sig;
	int rc;
	pthread_t ppid = pthread_self();

	pthread_detach(ppid);

	sigemptyset(&waitset);
	sigaddset(&waitset, SIGRTMIN);
	sigaddset(&waitset, SIGRTMIN + 2);
	sigaddset(&waitset, SIGRTMAX);
	sigaddset(&waitset, SIGUSR1);
	sigaddset(&waitset, SIGUSR2);

	while(1)
	{
		rc = sigwait(&waitset, &sig);
		if (rc != -1)
		{
			sig_handler(sig);
		}
		else
		{
			printf("sigwaitinfo() return err: %d; %s\n", errno, strerror(errno));
		}
	}
}

int main(int argc, char* argv[])
{
	sigset_t bset, oset;
	int i;
	pid_t pid = getpid();
	pthread_t ppid;

	sigemptyset(&bset);
	sigaddset(&bset, SIGRTMIN);
	sigaddset(&bset, SIGRTMIN + 2);
	sigaddset(&bset, SIGRTMAX);
	sigaddset(&bset, SIGUSR1);
	sigaddset(&bset, SIGUSR2);

	if (pthread_sigmask(SIG_BLOCK, &bset, &oset) != 0)
		printf("!! set pthread mask failed\n");

	kill(pid, SIGRTMAX);
	kill(pid, SIGRTMAX);
	kill(pid, SIGRTMAX + 2);
	kill(pid, SIGRTMIN + 2);
	kill(pid, SIGRTMIN);
	kill(pid, SIGRTMIN + 2);
	kill(pid, SIGRTMIN);
	kill(pid, SIGUSR2);
	kill(pid, SIGUSR2);
	kill(pid, SIGUSR1);
	kill(pid, SIGUSR1);

	pthread_create(&ppid, NULL, sigmgr_thread, NULL);

	sleep(10);

	exit(0);
}

