#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>

#define SA struct sockaddr
#define MAXLINE 256
#define LISTENQ 1024

int main(int argc, char* argv[])
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("socket error");
		exit(1);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(13);
	if(bind(listenfd, (SA*) &servaddr, sizeof(servaddr)) < 0){
		printf("bind error");
		exit(1);
	}
	if(listen(listenfd, LISTENQ)){
		printf("listen error");
		exit(1);
	}
	for(;;)
	{
		if((connfd = accept(listenfd, (SA*)NULL, NULL)) < 0)
			printf("accept error");
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		if(write(connfd, buff, strlen(buff)) < 0)
			printf("write error");
		if(close(connfd) < 0)
			printf("close error");
	}

}

