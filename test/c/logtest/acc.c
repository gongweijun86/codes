#include <unistd.h>
#include <stdio.h>

int 
main(int argc,char **argv)
{
	printf("%d",access("/home/orion/codes/test/c/",R_OK));
//	printf ( "%d\n",fopen("/home/orion/codes/test/c/a","a+"));
	FILE *f = fopen("/home/orion/codes/test/c/d/a","a+");
	return 0;
}
