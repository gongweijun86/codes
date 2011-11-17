#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <pthread.h>

static pthread_key_t key;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char** environ;
#define ARG_MAX 256

static void
thread_init(void)
{
	pthread_key_create(&key, free);
}

char* getenv(const char* name)
{
	int i;
	int len;
	char* envbuf;

	pthread_once(&init_done, thread_init);
	pthread_mutex_lock(&env_mutex);
	envbuf = (char*)pthread_getspecific(key);
	if(envbuf == NULL)
	{
		printf("envbuf is null \n");
		envbuf = malloc(ARG_MAX);
		if(envbuf == NULL)
		{
			pthread_mutex_unlock(&env_mutex);
			return NULL;
		}
		pthread_setspecific(key, envbuf);
	}
	len = strlen(name);
	for(i = 0; environ[i] != NULL; i++)
	{
		if((strncmp(name, environ[i], len) == 0) && (environ[i][len] == '='))
		{
			strcpy(envbuf, &environ[i][len+1]);
			pthread_mutex_unlock(&env_mutex);
			printf("---------------------\n");
			sleep(2);
			return envbuf;
		}
	}
	pthread_mutex_unlock(&env_mutex);
	return NULL;
}

void*
thr_fn1(void* arg)
{
	printf("thread 1 : %s\n",getenv("HOME"));
}

void* 
thr_fn2(void* arg)
{
	printf("thread 2 :%s\n",getenv("USER"));
}

int main(int argc, char* argv[])
{
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, thr_fn1, NULL);
	pthread_create(&tid2, NULL, thr_fn2, NULL);
	printf("main thread:%s\n",getenv("PATH"));
	sleep(1);
	exit(0);
}

