#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

void func(void* arg)
{
	pthread_detach(pthread_self());
	sleep(10);
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t tid;
	pthread_create(&tid, NULL, (void*)&func, NULL);

	sleep(5);
	printf("kill thread %lu\n",tid);
	pthread_kill(tid, SIGKILL);
	sleep(5);
	printf("main thread exit\n");

	return 0;
}

