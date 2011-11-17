#include <stdio.h>
int main()
{
const int max = 80;
char name[max];
char fmt[10];
sprintf(fmt, "%%%ds", max - 1);
int i;
scanf(fmt, name);
printf("%s\n", name);
}
