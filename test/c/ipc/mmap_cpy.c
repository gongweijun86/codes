#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define handler_error(msg) \
	do { perror(msg); exit(1);}while(0)

int main(int argc, char* argv[])
{
	int fdin, fdout;
	void* src, *dst;
	struct stat statbuf;

	if (argc != 3)
		handler_error("usage: ./a.out <fromfile> <tofile>\n");

	if ((fdin = open(argv[1], O_RDONLY)) < 0)
		handler_error("open:");

	if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 00644)) < 0)
		handler_error("open:");

//	fprintf(stdout, "%d\n", statbuf.st_size);
	if (fstat(fdin, &statbuf) < 0)
		handler_error("fstat:");

//	fprintf(stdout, "%d\n", statbuf.st_size);
	/* set size fo output file */
	if (lseek(fdout, statbuf.st_size - 1, SEEK_SET) == -1)
		handler_error("lseek:");

	if (write(fdout, "", 1) != 1)
		handler_error("write:");
//	fstat(fdout, &statbuf);
//	fprintf(stdout, "%d\n", statbuf.st_size);

	if ((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) == MAP_FAILED)
		handler_error("mmap:");
	if ((dst = mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0)) == MAP_FAILED)
		handler_error("mmap:");

	memcpy(dst, src, statbuf.st_size);
	exit(0);
}

