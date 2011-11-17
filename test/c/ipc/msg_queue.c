#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>

struct mymsg
{
	long msg_type;
	char msg_text[512];
};


int main(int argc, char* argv[])
{
	int qid;
	key_t key;
	int len;

	struct mymsg msg;
	if ((key = ftok(".",'b') == -1))
	{
		perror("create key error\n");
		exit(1);
	}

	if ((qid = msgget(key, IPC_CREAT | 0666)) == -1)
	{
		perror("create msg error\n");
		exit(1);
	}

	printf("create open queue qid is %d\n", qid);
	fputs("please input message: ",stdout);
	if ((fgets((&msg)->msg_text, 512, stdin)) == NULL)
	{
		perror("no message\n");
		exit(1);
	}

	msg.msg_type = getpid();
	len = strlen(msg.msg_text);
	printf("sending msg...\n");
	if((msgsnd(qid, &msg, len, 0)) < 0)
	{
		perror("send message error\n");
		exit(1);
	}

	printf("reading msg...\n");
	if ((msgrcv(qid, &msg, 512, 0, 0)) < 0)
	{
		perror("read msg error\n");
		exit(1);
	}

	printf("received msg is: %s\n", (&msg)->msg_text);

	if ((msgctl(qid, IPC_RMID, NULL)) < 0)
	{
		perror("delete msg error\n");
		exit(1);
	}

	exit(0);
}

