#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <socket.h>


#define SERV_PORT 9999


void str_echo(int sockfd)
{
	ssize_t n;
	char buf[128];

again:
	while ((n = read(sockfd, buf, 128)) > 0)
	{
		writen(sockfd, buf, n);
	}

	if (n > 0 && errno == EINTR) 
	{
		goto again:
	}
	else if (n < 0)
	{
		perror("str_echo read error!");
		exit(1);
	}
}

int main(int argc, char* argv[])
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket:");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr,sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("bind:");
		exit(1);
	}

	if (listen(listenfd, LISTENQ) < 0)
	{
		perror("listen:");
		exit(1);
	}

	for (;;)
	{
		clilen = sizeof(cliaddr);
		if ((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen)) < 0)
		{
			perror("accept:");
			exit(1);
		}

		if ((childpid = fork()) == 0)
		{
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}
}

