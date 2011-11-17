#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define WPORT 9999
#define BUFSIZE 1000

int clntdesc;
int svrdesc;

char outbuf[BUFSIZE];

void respond()
{
	int fd, nb;

	memset(outbuf, 0, sizeof(outbuf));
	system("w > tmp.client");
	fd = open("tmp.client", O_RDONLY);
	nb = read(fd, outbuf, BUFSIZE);
	write(clntdesc, outbuf, nb);
	unlink("tmp.client");
	close(clntdesc);
}

int main(void)
{
	struct sockaddr_in bindinfo;

	svrdesc = socket(AF_INET, SOCK_STREAM, 0);
	bindinfo.sin_family = AF_INET;
	bindinfo.sin_port = WPORT;
	bindinfo.sin_addr.s_addr = INADDR_ANY;
	bind(svrdesc, (struct sockaddr *)&bindinfo, sizeof(bindinfo));

	listen(svrdesc, 5);

	while(1)
	{
		clntdesc = accept(svrdesc, 0, 0);
		respond();
	}
}
