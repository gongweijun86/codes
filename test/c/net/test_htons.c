#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>


void print_binary(int n)
{
	int i;
	int temp[32];
	for (i = 0; i < 32; i++)
	{
		temp[31 - i] = n & 0x0001;
		n = n >> 1;
	}
	//printf("%s", temp);
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

//	print_binary(0x1111);

	uint32_t h2nl = htonl(atoi(argv[1]));
	printf("htonl: %d\n", h2nl);
	print_binary(h2nl);
	uint32_t n2hl = ntohl(h2nl);
	printf("ntohl: %d\n", n2hl);
	print_binary(n2hl);
	
	exit(0);
}

