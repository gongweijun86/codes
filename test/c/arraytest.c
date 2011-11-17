#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int (*x)[4];
	int y[4]={1,2,3,4};
	x = y;

	int i;
	for(i = 0; i < 4; i++)
	{
		printf("%i\n",(*x)[i]);
		printf("%i\n",y[i]);
		
	}
	printf("%x\n",x);
	printf("%x\n",y);
	printf("%x\n",*x);

}

