#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void my_exit1(void)
{
	printf("first exit handler\n");
}

static void my_exit2(void)
{
	printf("second exit handler\n");
}


int main(int argc, char* argv[])
{
	if(atexit(my_exit2) != 0)
		printf("cann't register myexit2'");
	if(atexit(my_exit1) != 0)
		printf("cann't register myexit1'");
	if(atexit(my_exit1) != 0)
		printf("cann't register myexit1'");
	printf("main is done!\n");
//	return(0);
}

