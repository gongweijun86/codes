#include <stdio.h>

int main(void)
{
	int a[5];
	printf("      a:%x\n",a);
	printf("    a+1:%x\n",a+1);
	printf("     &a:%x\n",&a);
	printf("   &a+1:%x\n",&a+1);
	printf("&a[0]+1:%x\n",&a[0]+1);
}
