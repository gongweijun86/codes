#include "func__fd.h"

int func_recv_fd(int recv_sock, int* recvfd, void* data, int bytes)
{
	struct msghdr msghead;
	struct iovec passdata[1];
	int ret;
	int temp;
	int newfd;


	memset(&msghead, 0, sizeof(msghead));

	/* fufill the structure */
	msghead.msg_name = NULL;
	msghead.msg_namelen = 0;
	passdata[0].iov_base = data;
	passdata[0].iov_len = bytes;

	msghead.msg_iov = passdata;
	msghead.msg_iovlen = 1;

	/* recv fd */
	union{
	        struct cmsghdr cm;
		char control[CMSG_SPACE(sizeof(int))];
	}control_un;
        struct cmsghdr *cmptr;
	msghead.msg_control = control_un.control;
	msghead.msg_controllen = sizeof(control_un.control);
	if((ret = recvmsg(recv_sock, &msghead, 0)) <= 0)
	{
	        return ret;
	}
	cmptr = CMSG_FIRSTHDR(&msghead);
        if((cmptr != NULL) && (cmptr->cmsg_len == CMSG_LEN(sizeof(int))))
	{
	        if(cmptr->cmsg_level != SOL_SOCKET)
	        {
	                return (-1);
	        }
	        if(cmptr->cmsg_type != SCM_RIGHTS)
	        {
	                return (-1);
	        }
	        *recvfd = *((int*)CMSG_DATA(cmptr));
	}
	else
	{
	        if(cmptr == NULL)
			*recvfd = -1; // descriptor was not passed
	}
	        
	return ret;
}

int func_send_fd(int send_sock, int send_fd, void* data, int bytes)
{
	struct msghdr msghead;
	struct iovec passdata[1];
	int ret;

	union{
	        struct cmsghdr cm;
	        char control[CMSG_SPACE(sizeof(int))];
	}control_un;
	struct cmsghdr *cmptr;
	msghead.msg_control = control_un.control;
	msghead.msg_controllen = sizeof(control_un.control);
	cmptr = CMSG_FIRSTHDR(&msghead);
	cmptr->cmsg_len = CMSG_LEN(sizeof(int));
	cmptr->cmsg_level = SOL_SOCKET;
	cmptr->cmsg_type = SCM_RIGHTS;
	*((int*)CMSG_DATA(cmptr)) = send_fd;

	msghead.msg_name = NULL;
	msghead.msg_namelen = 0;
	passdata[0].iov_base = data;
	passdata[0].iov_len = bytes;

	msghead.msg_iov = passdata;
	msghead.msg_iovlen = 1;

	/* send messages */
	if ((ret = sendmsg(send_sock, &msghead, 0)) < 0)
	{
		perror("sendmsg:");
		exit(-1);
	}

	return ret;
}

