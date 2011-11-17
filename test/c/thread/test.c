#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	void* a = (void*)5;
	printf("%d\n",(int)a);
	void* b;
	printf("%x\n",b);
	void* c;
	printf("%x\n",c);
	printf("%x\n",&c);
	printf("%d\n",sizeof(b));
}

