#include <string.h>
#include <stdio.h>

int main(void)
{
	printf("%d\n",sizeof("1222/11/11 12:22:22") - 1);
	printf("%d\n",strlen("1222/11/11 12:22:22"));
}
