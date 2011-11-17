#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define MAX_N 1000
#define MAX_THREADS 100

int nthreads;
int n;
int prime[MAX_N + 1];
int nextbase;

int work[MAX_THREADS];

pthread_mutex_t nextbaselock = PTHREAD_MUTEX_INITIALIZER;
pthread_t id[MAX_THREADS];

void crossout(int k)
{
	int i;
	for (i = k; i * k <= n; i++)
	{
		prime[i * k] = 0;
	}
}

void *worker(int tn)
{
	int lim;
	int base;

	lim = sqrt(n);

	do
	{
		pthread_mutex_lock(&nextbaselock);
		base = nextbase += 2;
		pthread_mutex_unlock(&nextbaselock);

		if (base <= lim)
		{
			work[tn]++;
			if (prime[base])
				crossout(base);
		}
		else
			return;
	}while(1);
}

int main(int argc, char **argv)
{
	int nprime;
	int towork;
	int i;
	
	void *p;

	n = atoi(argv[1]);
	nthreads = atoi(argv[2]);

	for (i = 2; i <= n; i++)
	{
		prime[i] = 1;
	}
	crossout(2);
	nextbase = 1;

	for (i = 0; i < nthreads; i++)
	{
		pthread_create(&id[i], NULL, (void *)worker, (void *)i);
	}

	towork = 0;

	for (i = 0; i < nthreads; i++)
	{
		pthread_join(id[i], &p);
		printf("%d values of base done\n", work[i]);
		towork += work[i];
	}
	printf("%d total values of base done\n", towork);

	nprime = 0;
	for (i = 2; i <= n; i++)
		if (prime[i])
		{
			nprime++;
			printf("%d ", i);
		}
	printf("\nthe number of primes found was %d\n", nprime);
}
