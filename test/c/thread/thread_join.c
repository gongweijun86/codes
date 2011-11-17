#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define THREADNUM 4


void* fun(void* arg)
{
	int i;
	long tid;
	double result = 0.0;
	tid = (long)arg;
	printf("thread %ld starting...\n",tid);
	for(i = 0; i < 100; i++)
	{
		result = result + sin(i)*tan(i);
	}
	printf("thread %ld done,Result = %e\n",tid, result);
	pthread_exit((void*)arg);
}


int main(int argc, char* argv[])
{
	pthread_t thread[THREADNUM];
	pthread_attr_t attr;
	int rc;
	long t;
	void* status;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for(t = 0; t < THREADNUM; t++)
	{
		printf("main: creating thread %ld\n",t);
		rc = pthread_create(&thread[t], &attr, fun, (void*)t);
		if(rc)
		{
			printf("error:%d\n",rc);
			exit(1);
		}
	}
	pthread_attr_destroy(&attr);
	for(t = 0; t < THREADNUM; t++)
	{
		sleep(1);
		rc = pthread_join(thread[t], &status);
		if(rc)
		{
			printf("error: %ld\n",t);
			exit(-1);
		}
		printf("main: complete join with thread %ld having status of %ld\n",t, (long)status);
	}
	printf("main: program complete,exiting.\n");
	pthread_exit(NULL);
}

