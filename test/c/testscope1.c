#include <stdio.h>
#include "testscope3.h"

extern int a;
extern PIDList pidlist;
void mainfun()
{
	fun();
}

int
main(int argc,char** argv)
{
	a = 0;
	printf("main:%d",a);
	mainfun();
	init_pidlist(&pidlist);	
	fun2();
}
