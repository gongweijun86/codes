#include <stdio.h>
#include "testscope3.h"
int a = 9;

extern PIDList pidlist;

void fun()
{
	printf("fun():%d\n",a);
}
void fun2()
{
	int i = 0;
	for(i=0;i<5;i++)
		printf("pidlits->PID[%d]:%d\n",i,pidlist.PID[i]);
}

