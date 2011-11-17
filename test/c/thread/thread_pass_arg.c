#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_NUM 5

void* fun(void* arg)
{
	long tid;
	
	tid = (long)arg;
	printf("hello world!\tthis is thread %ld!\n",tid);
	pthread_exit(NULL);
}


int main(int argc, char* argv[])
{
	pthread_t threads[THREAD_NUM];
	int rc;
	long t;
	for(t = 0; t < THREAD_NUM; t++)
	{
		printf("In main: creating thread %ld\n",t);
		rc = pthread_create(&threads[t], NULL, fun, (void*)t);
		if(rc)
			printf("error:%d\n",rc),exit(-1);
	}
	pthread_exit(NULL);
}

