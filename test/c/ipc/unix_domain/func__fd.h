#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

int func_recv_fd(int recv_sock, int* recv_fd, void* data, int bypes);
int func_send_fd(int send_sock, int send_fd, void* data, int bypes);
