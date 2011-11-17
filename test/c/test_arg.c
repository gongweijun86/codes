#include <stdarg.h>
#include <stdio.h>

void fun(int arg, ...)
{
	va_list start;
	va_start(start,arg);
	float f = va_arg(start,float);
	printf("%f\n",f);
}


int
main(int argc, char** argv)
{
	int a = 9;
	float b = 0.9;
	fun(a,b);
}
