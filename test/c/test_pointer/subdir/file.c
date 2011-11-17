#include "file.h"

void* fun()
{
	B* b;
	b = (B*)malloc(sizeof(B));
	b->a = 1;
	b->b = 2;
	b->c[0] = 5;
	return b;
}
