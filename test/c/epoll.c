#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MAXBUF 1024
#define MAXEPOLLSIZE 10000

int setnonblocking(int sockfd)
{
	if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK) == -1)
	{
		return -1;
	}

	return 0;
}

int handle_message(int new_fd)
{
	char buf[MAXBUF + 1];
	int len;

	bzero(buf, MAXBUF + 1);
	len = recv(new_fd, buf, MAXBUF, 0);
	if (len > 0)
	{
		printf("%d接收消息成功：%s,共%d个字节\n",new_fd, buf, len);
	}
	else
	{
		if (len < 0)
		{
			printf("接受消息失败！错误代码：%d,错误信息：%s\n",errno, strerror(errno));
			close(new_fd);
			return -1;
		}
	}
	return len;
}



int main(int argc, char* argv[])
{
	int listener, new_fd, kdpfd, nfds, n, ret, curfds;
	socklen_t len;
	struct sockaddr_in my_addr, their_addr;
	unsigned int myport, lisnum;
	struct epoll_event ev;
	struct epoll_event events[MAXEPOLLSIZE];
	struct rlimit rt;
	myport = 5000;
	lisnum = 2;
	rt.rlim_max = rt.rlim_cur = MAXEPOLLSIZE;
	if (setrlimit(RLIMIT_NOFILE, &rt) == -1)
	{
		perror("setrlimt");
		exit(1);
	}
	else
	{
		printf("设置资源参数成功\n");
	}

	if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	setnonblocking(listener);

	bzero(&my_addr, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(myport);
	my_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(listener, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("bind");
		exit(1);
	}
	else
	{
		printf("IP地址和端口绑定成功\n");
	}

	if (listen(listener, lisnum) == -1)
	{
		perror("listen");
		exit(1);
	}
	else
	{
		printf("开启服务成功\n");
	}

	kdpfd = epoll_create(MAXEPOLLSIZE);
	len = sizeof(struct sockaddr_in);
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = listener;

	if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, listener, &ev) < 0)
	{
		fprintf(stderr, "epoll set insertion error:fd = %d\n", listener);
		return -1;
	}
	else
	{
		printf("监听socket加入epoll成功\n");
	}

	curfds = 1;
	while(1)
	{
		nfds = epoll_wait(kdpfd, events, curfds, -1);
		if (nfds == -1)
		{
			perror("epoll_wait");
			break;
		}
		for (n = 0; n < nfds; n++)
		{
			if (events[n].data.fd == listener)
			{
				new_fd = accept(listener, (struct sockaddr*)&their_addr, &len);
				if (new_fd < 0)
				{
					perror("accept");
					continue;
				}
				else
				{
					printf("有连接来自：%s ；%d, 分配socket为%d\n", inet_ntoa(their_addr.sin_addr), ntohs(their_addr.sin_port), new_fd);
				}
				setnonblocking(new_fd);
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = new_fd;
				if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, new_fd, &ev) < 0)
				{
					fprintf(stderr, "把socket ‘%d’加入epoll失败!%s \n", new_fd, strerror(errno));
					return -1;
				}
				curfds++;
			}
			else
			{
				ret = handle_message(events[n].data.fd);
				if (ret < 1 && errno != 11)
				{
					epoll_ctl(kdpfd, EPOLL_CTL_DEL, events[n].data.fd, &ev);
					curfds--;
				}
			}
		}
	}
	close(listener);
	exit(0);

}

