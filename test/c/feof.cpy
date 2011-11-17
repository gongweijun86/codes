#include <stdio.h>
#define MAXLINE 256
int 
main()
{
	char buf[MAXLINE];
	FILE* infp = fopen("/home/orion/codes/test/c/feof.c","rt");
	FILE* outfp = fopen("/home/orion/codes/test/c/feof.cpy","wt");
	while(!feof(infp)) 
	{ 
		fgets(buf, MAXLINE, infp); 
		fputs(buf, outfp); 
	}
}
//this is the end!!!!!!
//this is the end!!!!!!
