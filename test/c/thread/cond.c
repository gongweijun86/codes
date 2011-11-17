#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int x,y;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void
ok()
{
	pthread_mutex_lock(&lock);
	while(x < y)
	{
		pthread_cond_wait(&cond, &lock);
	}
	printf("ok, i see now x >= y!\n");
	pthread_mutex_unlock(&lock);

}
void*
setxlty(void* arg)
{
	printf("call function setxlty()\n");
	printf("thread1 sleeping../\n");
	sleep(3);
	x = 3;
	y = 2;
	pthread_cond_signal(&cond);
	printf("call function setxlty() finished\n");
}


int main(int argc, char* argv[])
{
	pthread_t tid1;
	pthread_create(&tid1,NULL,setxlty,NULL);
	x = 1;
	y = 2;
	printf("test start...\n");
	printf("call function ok()\n");
	ok();
	printf("call function ok() finished\n");
}

