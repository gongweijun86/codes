#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <time.h>
#include <sys/ipc.h>

#define SEGSIZE 1024
#define READTIME 1

union semun
{
	int val;
	struct semid_ds* buf;
	unsigned short* array;
}arg;

void out_time(void)
{
	static long start = 0;
	time_t tm;
	if (start == 0)
	{
		tm = time(NULL);
		printf("now start...\n");
	}
	printf("second: %ld\n",(long)(time(NULL)) - start);
}

int new_sem(key_t key)
{
	union semun sem;
	int semid;
	sem.val = 0;
	semid = semget(key, 0, 0);
	if(semid == 0)
	{
		perror("create semaphore error\n");
		exit(-1);
	}
	return semid;
}

void wait_v(int semid)
{
	struct sembuf sops = {0, 0, 0};
	semop(semid, &sops, 1);
}
int main(int argc, char* argv[])
{
	key_t key;
	int shmid, semid;
	char* shm;
	char msg[100];
	char i;

	key = ftok("/", 0);
	shmid = shmget(key, SEGSIZE, 0);
	if (shmid == -1)
	{
		perror("create shared memory error\n");
		exit(-1);
	}

	shm = (char*)shmat(shmid, 0, 0);
	if ((int)shm == -1)
	{
		perror("attach shared memory error\n");
		exit(1);
	}

	semid = new_sem(key);

	for (i = 0; i <= 3; i++)
	{
		sleep(2);
		wait_v(semid);
		printf("Message got is : %s \n", shm + 1);
		out_time();
	}

	shmdt(shm);
	exit(0);
}

