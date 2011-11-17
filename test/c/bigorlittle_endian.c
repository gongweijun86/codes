#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int n = 0x12345678;
	char* p = (char*)&n;

	if(*p == 0x12)
		printf("big endian\n");
	else
		printf("little endian\n");
}

