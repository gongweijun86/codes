#include <string.h>
#include <stdio.h>

int main()
{
	char str1[] = "a.b.c.d:1111"; 
	char *str[] = {str1};
	char *tmp = strsep(str, ".");
	char *t = strsep(str, ".");
	char *m = strsep(str, ".");
	char *p = strsep(str, ".");
	printf("%s\n", tmp);
	printf("%s\n", str1);
	printf("%s\n", t);
	printf("%s\n", str1);
	printf("%s\n", m);
	printf("%s\n", str1);
	printf("%s\n", p);
	printf("%s\n", str1);
}
