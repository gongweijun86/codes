#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

void print_binary(int n)
{
        int i;
        int temp[32];
	for (i = 0; i < 32; i++)
	{
	        temp[31 - i] = n & 0x0001;
	        n = n >> 1;
	}
	for (i = 0; i < 32; i++)
	{
		if (i % 8 == 0)
		    printf("  ");
		printf("%d",temp[i]);
	}
	printf("\n");
}

int main(int argc, char* argv[])
{	
	if (argc != 2)
	{
		perror("arg not enough:");
		exit(1);
	}

	int ret;
	char* str;
	char res[128];
	struct in_addr addr;

	if ((ret = inet_pton(AF_INET, argv[1], &addr)) == 0)
	{
		perror("inet_pton:");
		exit(1);
	}

	printf("%d\n",addr.s_addr);
	print_binary(addr.s_addr);
	
	str = inet_ntop(AF_INET, &addr, res, sizeof(res));
	if ( str == NULL)
	{
		perror("inet_ntop:");
		exit(1);
	}

	printf("%s\n", res);

	exit(0);
}

