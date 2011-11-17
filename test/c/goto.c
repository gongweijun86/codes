#include <stdio.h>
int main()
{
	printf("abcde\n");
	goto a;
	printf("after goto a\n");
	goto b;
	printf("after goto b\b");
a:
	printf("in a:\n");
b:
	printf("in b:\n");
	
	printf("end\n");
	
	return 0;
}
