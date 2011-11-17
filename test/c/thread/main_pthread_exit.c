#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void* fun(void* arg)
{
	sleep(2);
	printf("fun\n");
	pthread_exit(NULL);
}


int main(int argc, char* argv[])
{
	pthread_t tid;

	pthread_create(&tid, NULL, fun, NULL);
	printf("main\n");
	//pthread_exit(NULL);
	exit(0);
}

