#include "structure.h"

void structure(int flag)
{
	switch(flag)
	{
		case 1:
			branch1(1);
			break;
		case 2:
			branch2(2);
			break;
		default:
			//branch1(1);
			//branch2(2);
			printf("you are int structure default!!!\n");
			break;
	}
}
