#include <stdio.h>
#include <stdint.h>
int 
main(int argc, char **argv)
{
	char a = 1;
	uint64_t time = (a << 32) | (a<<24) | (a<<16) | (a<<8) | a ;
	printf("%llu\n",time);
}
