#include <stdio.h>

int
main(int argc,char **argv)
{
	FILE* f = fopen("/home/orion/Development/file/resource_for_test/ts/20100709_SVN_MUX_A.ts","rb");
	if(feof(f))
	{
		printf("end?--1--%ld",ftell(f));
	}
	printf("start?%ld",ftell(f));
	fseek(f,-1,SEEK_END);
	if(feof(f))
	{
		printf("end?--2--%ld",ftell(f));
	}
	char* buf;
	char a = buf[0];
	fread(buf,sizeof(char),1,f);
	if(feof(f))
	{
		printf("end?--3--%ld",ftell(f));
	}
	fread(buf,sizeof(char),4,f);
	if(feof(f))
	{
		printf("end?--4--%ld",ftell(f));
	}
	printf("%s\n",buf);	
}
