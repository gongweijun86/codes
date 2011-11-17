#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	unsigned int a = 1;
	unsigned int c = 124;
	int b;
	b = (unsigned int)a;
	printf("%d\n",b);
	if (a - c >= 0)
		printf("a<c\n");
	else
		printf("a>c\n");
	unsigned int m = 0xffffffff;
	unsigned int n = 0x7fffffff;
	int l;
	l = (int)m;
	printf("0xffffffff->int: %d %x\n",l,l);
	l = (int)n;
	printf("0x7fffffff->int: %d %x\n",l,l);

	int p = -1;
	unsigned int q = p;
	printf("int->unsigned: %u %0x\n",q,q);

	printf("%d\n",sizeof("-2147483648") - 1);
//	printf("%x\n",-2147483648);
	printf("%d\n,",sizeof("-9223372036854775808") - 1);
	printf("%d\n",sizeof("abcd"));
}

