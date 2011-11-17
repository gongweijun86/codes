#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char src[16] = "abcdefghijklmnop";
	char buf[4];
	strncpy(buf, src, strlen(src));
	printf("%s\n", buf);
	
}

