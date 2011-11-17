#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define LISTENQ 128

int main(int argc, char* argv[])
{
	int sockfd, n;
	struct sockaddr_in servaddr;
	char buff[128 + 1];

	if(argc != 2)
	{
		perror("not enough arg:");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket:");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <=0)
	{
		perror("inet_pton:");
		exit(1);
	}

	if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("connect:");
		exit(1);
	}

	while((n = read(sockfd, buff, 128)) > 0)
	{
		buff[n] = 0;
		if (fputs(buff, stdout) == EOF)
		{
			perror("fputs:");
			exit(-1);
		}
	}
	if (n < 0)
	{
		perror("read:");
		exit(1);
	}
	exit(0);
}

