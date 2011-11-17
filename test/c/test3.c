#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void f1()
{
	printf("f1()\n");
}
void f2()
{
	printf("f2()\n");
}


int main(int argc, char* argv[])
{
	void (*pf)(void);
	pf = f1;
	printf("%x\n",f1);
	printf("%x\n",*f1);
	printf("%x\n",pf);
	printf("%x\n",*pf);
	pf = f2;
	printf("%x\n",f2);
	printf("%x\n",*f2);
	printf("%x\n",pf);
	printf("%x\n",*pf);
	f1 = f2;
	printf("%x\n",f1);
	printf("%x\n",*f1);
	printf("%x\n",f2);
	printf("%x\n",*f2);

}

