#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stropts.h>
//#include <sys/conf.h>

int main(int argc, char* argv[])
{
	int fd, i, nmods;
	struct str_list list;

	if(argc != 2)
		printf("argc not enough");
	if((fd = open(argv[1], O_RDONLY)) < 0)
		printf("cannot open %s\n",argv[1]);

	if((nmods = ioctl(fd, I_LIST, (void*)0)) < 0)
		printf("I_LIST error");
	printf("#modules = %d\n",nmods);

	list.sl_modlist = calloc(nmods, sizeof(struct str_mlist));
	if(list.sl_modlist == NULL)
		printf("calloc error");
	list.sl_nmods = nmods;

	if(ioctl(fd, I_LIST, &list) < 0)
		printf("I_LIST error");
	for(i = 1; i < nmods; i++)
	{
		printf(" %s: %s\n", (i == nmods)? "driver" : "module",list.sl_modlist++ -> l_name);
	}
	exit(0);
	
}

