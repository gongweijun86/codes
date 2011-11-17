#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FILEMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char* argv[])
{
	int fd;
	struct stat statbuf;

	if((fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, FILEMODE)) < 0)
		printf("error for open:%s\n", argv[1]);
	if(fstat(fd, &statbuf) < 0)
		printf("stat error\n");
	printf("%s's size is : %d\n",argv[1], (int)statbuf.st_size);
	if(lseek(fd, 100, SEEK_SET) == -1)
		printf("lseek error\n");
	if(fstat(fd, &statbuf) < 0)
		printf("stat error\n");
	printf("%s's size is : %d\n",argv[1], (int)statbuf.st_size);

	if(write(fd, "1", 1) != 1)
		printf("write error\n");
	if(fstat(fd, &statbuf) < 0)
		printf("stat error\n");
	printf("%s's size is : %d\n",argv[1], (int)statbuf.st_size);
	exit(0);
}

