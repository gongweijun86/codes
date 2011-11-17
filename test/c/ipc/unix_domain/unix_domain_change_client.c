#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/un.h>

#define SLEEPTIME 3
#define ARGLEN 20


int main(int argc, char* argv[])
{
	int sockfd, recvfd, ret;

	struct sockaddr_un addr_client;
	int length, buflen;
	char data[10];
	ssize_t size;
	const char path[] = "./father";
	char buf[] = "this is client process ccc\n";

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("socket:");
		exit(-1);
	}

	addr_client.sun_family = AF_UNIX;
	strcpy(addr_client.sun_path, path);
	length = sizeof(addr_client.sun_family) + sizeof(addr_client.sun_path);

	ret = connect(sockfd, (struct sockaddr*)&addr_client, length);
	if (ret == -1)
	{
		perror("connect:");
		close(sockfd);
		exit(-1);
	}

	ret = func_recv_fd(sockfd, &recvfd, data, sizeof(data));
	if (ret == -1)
	{
		perror("func_recv_fd:");
		close(sockfd);
		exit(-1);
	}

	size = -1;
	buflen = sizeof(buf);

	if ((size = write(recvfd, buf, buflen)) <= 0)
	{
		perror("write:");
		exit(-1);
	}

	fprintf(stdout, "client write over!\n");

	exit(0);
}

