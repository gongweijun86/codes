#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <string.h>

#define SEGSIZE 1024
#define READTIME 1

union semun
{
	int val;
	struct semid_ds* buf;
	unsigned short* array;
}arg;

int sem_create(key_t key)
{
	union semun sem;
	int semid;
	sem.val = 0;
	semid = semget(key, 1, IPC_CREAT | 0666);
	if (semid == -1)
	{
		perror("create smmaphore error\n");
		exit(-1);
	}
	semctl(semid, 0, SETVAL, sem);
	return semid;
}

void del_sem(int semid)
{
	union semun sem;
	sem.val = 0;
	semctl(semid, 0, IPC_RMID, sem);
}

int p(int semid)
{
	struct sembuf sops = {0, +1, IPC_NOWAIT};
	return (semop(semid, &sops, 1));
}

int v(int semid)
{
	struct sembuf sops = {0, -1, IPC_NOWAIT};
	return (semop(semid, &sops, 1));
}

int main(int argc, char* argv[])
{
	key_t key;
	int shmid, semid;
	char* shm;
	char msg[7] = "-data-";
	char i;
	struct semid_ds buf;

	key = ftok("/", 0);
	shmid = shmget(key, SEGSIZE, IPC_CREAT | 0604);
	if (shmid == -1)
	{
		perror("create shared memory error\n");
		exit(-1);
	}

	shm = (char*)shmat(shmid, 0, 0);
	if ((int)shm == -1)
	{
		perror("attach shared memeory error\n");
		exit(-1);
	}

	semid = sem_create(key);

	for (i = 0; i <= 3; i++)
	{
		sleep(1);
		p(semid);
//		sleep(READTIME);
		msg[5] = '0' + i;
		memcpy(shm, msg, sizeof(msg));
		sleep(2);
		v(semid);
	}

	shmdt(shm);
	shmctl(shmid, IPC_RMID, &buf);
	del_sem(semid);
	
	exit(0);
}

