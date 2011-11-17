#include <stdio.h>
#include "erm_commnu_module.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(void)
{

	int sockfd[2];
	socketpair(AF_LOCAL, SOCK_STREAM, 0, sockfd);
	
	int pid;
	int c = 0;
	int sd;
	int status;

	if ((pid = fork()) > 0)
	{
		close(sockfd[1]);
		read_fd(sockfd[0], &c, sizeof(int), &sd);
		fprintf(stderr, "read fd is : %d\n", sd);
		
	}
	close(sockfd[0]);

	int fd = open("/home/orion/codes/test/c/erm/erm_commnu_module.h",O_RDONLY);
	write_fd(sockfd[1], (void *)&c, sizeof(int), fd);
	fprintf(stderr, "write fd is : %d\n", fd);
	if (waitpid(pid, &status, 0) != 0 )
	{
		perror("waitpid");
		exit(1);
	}
	return 0;
}
