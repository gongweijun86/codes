#include <stdio.h>

int j=0;
void f()
{
	int i=1;
	char c[10];
	for (j=0; j <= 10; j++)
		c[j]=0;
	printf("%d\n",i);



}
void ff()
{
int i;
int c[10];
printf("%d\n",sizeof(c));
printf("%d\n",sizeof(int));
for(i=0;i<10;i++)
		printf("%d\n",c[i]);

	for(i=0;i<sizeof(c)/sizeof(int);i++)
		c[i]=0;   
	for(i=0;i<10;i++)
		printf("%d\n",c[i]);

}
int main()
{
		f();
		ff();
		return 0;
}
