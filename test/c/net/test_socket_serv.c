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
	int listenfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
	char buff[128];
	time_t ticks;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket:");
		exit(-1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(9999);

	if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("bind:");
		exit(1);
	}

//	if (listen(listenfd, LISTENQ) < 0)
//	{
//		perror("listen:");
//		exit(1);
//	}

	for(;;)
	{
		len = sizeof(cliaddr);
		if ((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len)) < 0)
		{
			perror("accept:");
			exit(-1);
		}

		printf("connection from: %s, port %d\n",inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)), ntohs(cliaddr.sin_port));
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n",ctime(&ticks));
		int n;
		if ((n = write(connfd, buff, strlen(buff))) < 0)
		{
			perror("write:");
			exit(1);
		}

		close(connfd);
	}
}

