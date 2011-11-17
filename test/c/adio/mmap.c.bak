#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define FILEMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)


int main(int argc, char* argv[])
{
	int fdin, fdout;
	void* src;
	void* dst;
	struct stat statbuf;

	if(argc != 3)
		printf("arg not enough");
	if((fdin = open(argv[1], O_RDONLY)) < 1)
		printf("cannot open %s\n",argv[1]);
	if((fdout = open(argv[2],O_RDWR | O_CREAT | O_TRUNC, FILEMODE)) < 0)
		printf("cannot open %s\n",argv[2]);
	if(fstat(fdin, &statbuf) < 0)
		printf("fstat error");
	if(lseek(fdout, statbuf.st_size - 1, SEEK_SET) == -1)
		printf("lseek error");
	if(write(fdout, "" , 1) != 1)
		printf("write error");
	if((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) == MAP_FAILED)
		printf("map error for input");
	if((dst = mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0)) == MAP_FAILED)
		printf("map error for output");
	memcpy(dst, src, statbuf.st_size);
	exit(0);
}

