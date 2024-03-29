#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define WPORT 9999
#define BUFSIZE 1000

int main(int argc, char **argv)
{
	int sd;
	int msgsize;

	struct sockaddr_in addr;
	struct hostent *hostptr;
	char buf[BUFSIZE];

	sd = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = WPORT;
	hostptr = gethostbyname(argv[1]);
	memcpy(&addr.sin_addr.s_addr, hostptr->h_addr_list[0], hostptr->h_length);

	connect(sd, (struct sockaddr *)&addr, sizeof(addr));
	msgsize = read(sd, buf, BUFSIZE);

	if (msgsize > 0)
		write(1, buf, msgsize);
	printf("\n");
	return 0;
}
