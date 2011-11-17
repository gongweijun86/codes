#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>

void sig_handler(int signum)
{
	static int j = 0;
	static int k = 0;
	pthread_t sig_ppid = pthread_self();
	if (signum == SIGUSR1)
	{
		printf("thread %d, receive SIGUSR1 No,%d\n",sig_ppid, j)	;
		j++;
	}
	else
	{
		printf("thread %d, receive SIGRTMIN No,%d\n",sig_ppid, j);
		k++;
	}
}

void* worker_thread()
{
	pthread_t ppid = pthread_self();
	pthread_detach(ppid);
	while(1)
	{
		printf("I'm thread %d, I'm alive\n",ppid);
		sleep(10);
	}
}

void* sigmgr_thread()
{
	sigset_t waitset, oset;
	siginfo_t info;
	int rc;
	pthread_t ppid = pthread_self();

	pthread_detach(ppid);

	sigemptyset(&waitset);
	sigaddset(&waitset, SIGRTMIN);
	sigaddset(&waitset, SIGUSR1);

	while(1)
	{
		rc = sigwaitinfo(&waitset, &info);
		if (rc != -1 )
		{
			printf("sigwaitinfo() fetch the signal - %d\n", rc);
			sig_handler(info.si_signo);
		}
		else
		{
			printf("sigwaitinfo() returned err: %d, %s\n", errno, strerror(errno));
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
	sigaddset(&bset, SIGUSR1);
	if (pthread_sigmask(SIG_BLOCK, &bset, &oset) != 0)
		printf("!set pthread mask failed\n");

	pthread_create(&ppid, NULL, sigmgr_thread, NULL);

	for(i = 0; i < 5; i++)
	{
		pthread_create(&ppid, NULL, worker_thread, NULL);
	}

	for(i = 0; i < 5; i++)
	{
		kill(pid, SIGUSR1);
		printf("main thread, send SIGUSR1 No, %d\n", i);
		kill(pid, SIGRTMIN);
		printf("main thread, send SIGTMIN No, %d\n", i);
		sleep(2);
	}
	exit(0);
}

