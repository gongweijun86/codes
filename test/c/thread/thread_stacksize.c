#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>>

#define THREADNUM 4
#define N 1000
#define MEGEXTRA 1000000

pthread_attr_t attr;

void* dowork(void* arg)
{
	double A[N][N];
	int i, j;
	long tid;
	size_t mystacksize;

	tid = (long)arg;
	pthread_attr_getstacksize(&attr, &mystacksize);
	printf("thread %ld : stack size = %li bytes\n", tid, mystacksize);
	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++)
			A[i][j] = ((i * j) / 3.452) + (N - i);
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t thread[THREADNUM];
	size_t stacksize;
	int rc;
	long t;

	pthread_attr_init(&attr);
	pthread_attr_getstacksize(&attr, &stacksize);
	printf("default stacksize = %li \n", stacksize);
	stacksize = sizeof(double) * N * N + MEGEXTRA;
	printf("amount of stack needed per thread = %li bytes\n", stacksize);
	pthread_attr_setstacksize(&attr, stacksize);
	printf("creating threads with stack size = %li bytes \n", stacksize);
	for(t = 0; t < THREADNUM; t++)
	{
		rc = pthread_create(&thread[t], &attr, dowork, (void*)t);
		if(rc)
		{
			printf("error: %d", rc);
			exit(1);
		}
	}
	printf("create %ld threads\n",t);
	pthread_exit(NULL);
}

