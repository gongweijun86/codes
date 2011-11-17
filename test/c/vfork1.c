#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void f1(void), f2(void);

int main(int argc, char* argv[])
{
	f1();
	f2();
	_exit(0);
}

static void f1(void)
{
	pid_t pid;

	if((pid = vfork()) < 0)
		printf("vfork error");
	else if(pid == 0)
		printf("child:%d\n",getpid());
	else 
		printf("parent:%d\n",getpid());
}

static void f2(void)
{
//	char buf[10];
	int i;

//	for(i=0;i<sizeof(buf);i++)
//		buf[i]='a';
//	printf("pid=%d,%s\n",getpid(),buf);
	printf("f2---pid=%d\n",getpid());
}

