#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		perror("arg not enough:");
		exit(1);
	}

	int ret;
	char strptr[128];
	char* str = strptr;
	struct in_addr addrptr;
	if ((ret = inet_aton(argv[1], &addrptr) ==0))
	{
		perror("inet_aton:");
	}
	printf("addrptr: %d \n", addrptr.s_addr);

	str = inet_ntoa(addrptr);
	printf("ascii: %s \n", str);
	
	exit(0);
}

