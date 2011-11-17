#include <stdio.h>
#include <stdarg.h>
#include <string.h>
void func(int i, ...)
{
va_list args;
int j = 0;
int k = 0;
char c;
char str[32]={0};
//char *str;
va_start(args, i);
//j = va_arg(args, int);
//k = va_arg(args, int);
//c = va_arg(args, int);
//strcpy(str,va_arg(args, char*));
//str=va_arg(args, char*);
vsprintf(str,"aaaa%d,%d,%c,%s\n",args);
printf("%s",str);
va_end(args);
return;
}
void main(void)
{
func(1,2,3,'g',"hello world!");
}
