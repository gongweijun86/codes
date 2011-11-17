#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "recordlock.h"
#include "tellwait.h"

#define FILEMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

static void
lockabyte(const char* name, int fd, off_t offset)
{
	if(writew_lock(fd, offset, SEEK_SET, 1) < 0)
		printf("%s:writew_lock error", name);
	printf("%s got the lock, byte %ld\n", name, offset);
}

int main(int argc, char* argv[])
{
	int fd;
	pid_t pid;

	if((fd = creat("templock", FILEMODE)) < 0)
		printf("creat error");
	if(write(fd, "ab", 2) != 2)
		printf("write error");

	TELL_WAIT();
	if((pid = fork()) < 0)
		printf("fork error");
	else if(pid == 0)
	{
		lockabyte("child:", fd, 0);
		TELL_PARENT(getpid());
		WAIT_PARENT();
		lockabyte("child:", fd, 1);
	}
	else
	{
		lockabyte("parent:", fd, 1);
		TELL_CHILD(pid);
		WAIT_CHILD();
		lockabyte("parent:", fd, 0);
	}
	exit(0);
}

