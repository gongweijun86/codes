#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/un.h>


#include "func__fd.h"

#define SLEEPTIME 3
#define ARGLEN 20
#define MODE S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH /* -rwxr--r-- */
#define PERMIT O_RDWR | O_APPEND | O_CREAT

int main(int argc, char* argv[])
{
	int status, sockfd[2];
	char permit[ARGLEN];
	char mode[ARGLEN];
	char argsockfd[ARGLEN];
	int recvfd;
	char data[20];
	int bytes;
	int ret, i;
	size_t size;
	int buflen;
	pid_t pid, chldpid;

	/* unix domain needed paras */
	int fdsock, fdaccept;
	struct sockaddr_un addr_server;
	int len;
	const char path[] = "./father";

	/* father write to file */
	char buf[] = "paraent process write ppp\n";

	/* father write to client */
	char datasend[] = "send by myopen\n";

	memset(permit, '\0', sizeof(permit));
	memset(mode, '\0', sizeof(mode));
	memset(argsockfd, '\0', sizeof(argsockfd));
	memset(data, '\0', sizeof(data));

	fprintf(stdout, "father process, next fork()\n");
	sleep(SLEEPTIME);

	/* set open file mode and permition */
	snprintf(permit, sizeof(permit), "%d", PERMIT);
	snprintf(mode, sizeof(mode), "%d", MODE);

	/* establish the socket and pipe between the child and parent */
	ret = socketpair(AF_UNIX, SOCK_STREAM, 0, sockfd);
	if (ret < 0)
		perror("socketpair:");

	if ((chldpid = fork()) < 0)
	{
		perror("fork:");
		exit(-1);
	}
	else if(chldpid == 0)
	{
		close(sockfd[0]);
		fprintf(stdout, "child process, sendfock is %d\n", sockfd[1]);
		snprintf(argsockfd, sizeof(argsockfd), "%d\n", sockfd[1]);

		/* exec new program openfile */
		execl("./child", "child", permit, mode, argsockfd, (char*)NULL);
		fprintf(stdout, "execl failed, permit is %s, mode is %s\n", permit, mode);
		exit(-1);
	}
	fprintf(stdout, "parent:\n");
	close(sockfd[1]);
	bytes = sizeof(data);

	/* wait child to end */
	pid = wait(&status);
	if ((status = WEXITSTATUS(status)) == 0)
	{
		fprintf(stdout, "child %d process teminate, now parent will write to file\n", pid);
	}

	/* reveive the fd from child */
	ret = func_recv_fd(sockfd[0], &recvfd, data, bytes);
	if (ret < 0)
	{
		fprintf(stdout, "parent reveived failded\n");
		exit(-1);
	}
	else
	{
		fprintf(stdout, "parent recv %d data from fd: %d with data: %s\n", recvfd, strlen(data), data);
	}

	/*write to file*/
	size = -1;
	buflen = sizeof(buf);

	if ((size = write(recvfd, buf, buflen)) <= 0)
	{
		perror("write:");
		exit(-1);
	}

	/* ------------------------------------------- */
	/* parent establish the domain socket and wait for the client */
	fprintf(stdout, "parent write over,accept other process...\n");

	fdsock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (fdsock == -1)
	{
		perror("socket:");
		exit(-1);
	}

	unlink(path);

	memset(&addr_server, 0, sizeof(addr_server));
	addr_server.sun_family = AF_UNIX;
	strcpy(addr_server.sun_path, path);
	len = sizeof(struct sockaddr_un);

	ret = bind(fdsock, (struct sockaddr*)&addr_server, len);
	if (ret == -1)
	{
		perror("bind:");
		close(fdsock);
		unlink(path);
		exit(-1);
	}

	ret = listen(fdsock, 1);
	if ( ret == -1)
	{
		perror("listen:");
		close(fdsock);
		unlink(path);
	}

	fdaccept = accept(fdsock, (struct sockaddr*)&addr_server, &len);
	if (ret == -1)
	{
		close(fdsock);
		unlink(path);
		exit(-1);
	}

	/* send fd to client */
	ret = func_send_fd(fdaccept, recvfd, datasend, sizeof(datasend));
	if (ret < 0)
	{
		perror("func_send_fd:");
		exit(-1);
	}
	fprintf(stdout, "send fd over ! sleep 10's\n");
	sleep(10);

	exit(0);

}

