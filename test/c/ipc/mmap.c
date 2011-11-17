#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

void sig_bus()
{
	fprintf(stdout, "i am SIGBUS\n");
	exit(1);
}

void sig_seg()
{
	fprintf(stdout, "i am SIGSEGV\n");
	exit(1);
}


int main(int argc, char* argv[])
{
	int fd, i;
	int pagesize, offset;
	char* p_map;
	struct stat stat_buf;

	signal(SIGBUS, sig_bus);
	signal(SIGSEGV, sig_seg);

	/* get page size */
	pagesize = sysconf(_SC_PAGESIZE);
	fprintf(stdout, "pagesize is %d\n", pagesize);

	/* open file */
	fd = open(argv[1], O_RDWR, 00777);
	fstat(fd, &stat_buf);
	fprintf(stdout, "file size is %d\n", (size_t)stat_buf.st_size);

	/*  */
	offset = 0;
	p_map = (char*)mmap(NULL, pagesize * 2, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
	close(fd);

	p_map[stat_buf.st_size] = '9';
	p_map[pagesize] = '9';

	munmap(p_map, pagesize * 2);

	return 0;
}

