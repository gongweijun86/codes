#include <stdio.h>
void a()
{
volatile int array[10];
int i;
for (i = 0; i < 10; i++)
array[i] = i;
}
void b()
{
int array[10];
int i;
for (i = 0; i < 10; i++)
printf("%d\n",array[i]);
}
int main()
{
a();
b();
}
