#include <stdio.h>
#include "file.h"

int 
main(void)
{
	B* b = (B*)fun();
	printf("b->a:%d",b->a);
	printf("b->b:%d",b->b);
	printf("b->c[0]:%d",b->c[0]);
}
