#include <stdio.h>
#include <string.h>

int main()
{
	char str[] = "192.168.1.1:8888";
	char *flag = ".";
	char *tmpstr = strtok(str, flag);
	printf("%s\n",tmpstr);
	int port = atoi(strtok(NULL, ":"));
	printf("%d\n",port);

}
