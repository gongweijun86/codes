#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define SA struct sockaddr
#define MAXLINE 256
#include <string.h>

int main(int argc, char* argv[])
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if(argc != 2){
		printf("usage");
		exit(1);
	}
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("socket error");
		exit(1);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
		printf("inet_pton error");
		exit(1);
	}
	if(connect(sockfd, (SA*) &servaddr, sizeof(servaddr)) < 0){
		printf("connect error");
		exit(1);
	}
	while((n = read(sockfd, recvline, MAXLINE)) > 0)
	{
		recvline[n] = 0;
		if(fputs(recvline, stdout) == EOF){
			printf("fputs error");
			exit(1);
		}
	}
	if(n < 0){
		printf("read error");
		exit(1);
	}
	exit(0);
}

