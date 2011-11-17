#include "testscope3.h"

PIDList pidlist;

void init_pidlist(PIDList* pidlist)
{
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		(pidlist)->PID[i] = 0;
		(pidlist)->prognum[i] = 0;
	}
}
int isok(PIDList* pidlist)
{
	
}
