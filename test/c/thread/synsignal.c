#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

int quitflag;
sigset_t mask;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t wait = PTHREAD_COND_INITIALIZER;

void*
thr_fn(void* arg)
{
	int err, signo;
	for(;;)
	{
		err = sigwait(&mask, &signo);
		if(err != 0)
			printf("sigwait failed");
		switch(signo)
		{
			case SIGINT:
				printf("\ninterrupt\n");
				break;
			case SIGQUIT:
				pthread_mutex_lock(&lock);
				quitflag = 1;
				pthread_mutex_unlock(&lock);
				pthread_cond_signal(&wait);
				return 0;
			default:
				printf("unexpected singal :%d\n",signo);
				exit(1);
		}
	}
}

void
sig_int_handler()
{
	printf("u r in sig_int_handler\n");
}

void
sig_quit_handler()
{
	printf("u r in sig_quit_handler\n");
}
int main(int argc, char* argv[])
{
	int err;
	sigset_t oldmask;
	pthread_t tid;

	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, sig_quit_handler);

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);

	if((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0)
		printf("SIG_BLOCK err");
	err = pthread_create(&tid, NULL, thr_fn, 0);
	if(err != 0)
		printf("cannot create thread");
	pthread_mutex_lock(&lock);
	while(quitflag == 0)
		pthread_cond_wait(&wait, &lock);
	pthread_mutex_unlock(&lock);

	quitflag = 0;
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		printf("SIG_SETMASK err");
	exit(0);
}

