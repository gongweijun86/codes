#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void*
thr_fn1(void* arg)
{
	printf("thread 1 returning\n");
	sleep(1);
	return (void*)1;
}

void*
thr_fn2(void* arg)
{
	printf("thread 2 returning\n");
	pthread_exit((void*)2);
}

int main(int argc, char* argv[])
{
	int err;
	pthread_t tid1,tid2;
	void* tret;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if(err != 0)
		printf("cannot create thread 1:%s\n",strerror(err));
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if(err != 0)
		printf("cannot create thread 2:%s\n",strerror(err));
	err = pthread_join(tid1, &tret);
	if(err != 0)
		printf("cannot join with thread 1:%s\n",strerror(err));
	printf("thread 1 exit code %d\n",(int)tret);
	err = pthread_join(tid2, &tret);
	if(err != 0)
		printf("cannot join with thread 2:%s\n",strerror(err));
	printf("thread 2 exit code %d\n",(int)tret);
	exit(0);
}

