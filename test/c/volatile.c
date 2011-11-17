#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int x = 3;
int val1, val2;
//
//int val1, val2;
void* thr_fn(void* arg)
{
	x = 4;
	
//	printf("----------------------");
//	printf("x = %d \n",x);
//	printf("val1 = %d \n",val1);
//	printf("val2 = %d \n",val2);
//	printf("----------------------");
}

int main(int argc, char* argv[])
{
	val1 = x;

	pthread_t tid;
	pthread_create(&tid, NULL, thr_fn, NULL);

	sleep(1);

	val2 = x;
sleep(1)	;
	printf("x = %d \n",x);
	printf("val1 = %d \n",val1);
	printf("val2 = %d \n",val2);
}

