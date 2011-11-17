#include <stdio.h>

int main(void)
{
	void ****ptr;
	char *str;
	int *i;
	char a = 'a';
	int b = 123;
	str = &a;
	i = &b;

	ptr = str;
	printf("%c",*ptr);
	ptr = i;
	printf("\t%d\n",*ptr);
}
