#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

#include "func__fd.h"

#define SLEEPTIME 3
#define ARGLEN 20


int main(int argc, char* argv[])
{
	int i, fd, ret;
	ssize_t size;
	size_t buflen;
	char data[10];
	char buf[] = "open file prog write test\n";

	fd = -1;
	if ((fd = open("./file", atoi(argv[1]), atoi(argv[2]))) < 0)
	{
		perror("open:");
		exit(-1);
	}

	size = -1;
	buflen = sizeof(buf);
	if ((size = write(fd, buf, buflen)) <= 0)
	{
		perror("write:");
		exit(-1);
	}

	ret = 'a';
	for (i = 0; i < sizeof(data); i++)
	{
		data[i] = ret;
	}

	ret = -1;
	if ((ret = func_send_fd(atoi(argv[3]), fd, data, 10)))
	{
		perror("func_send_fd:");
	}
	close(fd);

	exit(0);
}

