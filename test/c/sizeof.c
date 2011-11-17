#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
struct s
{
	int a;
	int b;
	int c;
	char d[128];
};

struct s buf[5];

int main(int argc, char* argv[])
{
	fprintf(stdout, "sizeof(buf): %d\n", sizeof(buf));
}

