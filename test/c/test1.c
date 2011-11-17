#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int f(int val)
{
	int *ptr;
	if(val == 0)
	{
		int val;
		val = 5;
		ptr = &val;

	}
	return (*ptr + 1);
}

int main(int argc, char* argv[])
{
	printf("%d",f(8));
}

