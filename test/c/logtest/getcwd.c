#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int
main(int argc,char ** argv)
{
	char *str;
	str = (char *)malloc(sizeof(char) * 256);
//	str = getcwd(str,sizeof(str));
	str = getcwd(str,256);
	printf ( "%d\n",sizeof(str) );
//	printf ( "%d\n",strlen(str) );
	printf("%s",str);
	return 0;
}
