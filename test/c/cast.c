#include <stdio.h>

#define sig_err (void (*)(int))-1
#define sig_def (void (*)(int))0
#define sig_ign (void (*)(int))1

void fun();

int
main()
{
	fun(12,34);
}

void fun(int i, int j)
{
	printf("%d,%d\n",i,j);
	printf("sig_err:%d\n",(int)sig_err);
	printf("sig_def:%d\n",sig_def);
	printf("sig_ign:%d\n",sig_ign);
}
