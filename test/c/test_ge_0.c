#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int fun1(int n)
{
	if (n > 1)
		return 1;
	else if ( n == 1)
		return 0;
	else 
		return -1;
}

int fun2(int n)
{
	if (n > 1)
		return 1;
	else if (n == 1)
		return 0;
	else 
		return -1;
}

int fun3(int n)
{
	if (n > 1)
		return 1;
	else if (n == 1)
		return 0;
	else 
		return -1;
}

int  fun(int n)
{
	if(fun1(2) >= 0)
	{
		fun2(n)>=0;
		return 0;
	}
	else
		fun3(n);
	return -1;
}


int main(int argc, char* argv[])
{
	int n = -2;
	printf("fun: %d \n",fun(n));
	printf("end\n");
}

