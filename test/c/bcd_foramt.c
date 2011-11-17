#include <stdio.h>
#include <stdint.h>
#include <string.h>
int
main(void)
{
	uint32_t arg = 0x014530;
	char buf[8]={'a','a','a','a','a','a','a','a'};

	char* p = (char*)&arg;
	printf("%x\n",p[0]);	
	printf("%x\n",p[1]);
	printf("%x\n",p[2]);
	printf("%x\n",p[3]);

	printf("hour:%x\n",((&arg)[1]));
	printf("min:%x\n",((&arg)[2]));
	printf("sec:%x\n",((&arg)[3]));


/*	printf("%c\n",buf[0]);
	printf("%c\n",buf[1]);

	printf("%c\n",buf[2]);
	printf("%c\n",buf[3]);
	printf("%c\n",buf[4]);
	printf("%c\n",buf[5]);
	printf("%c\n",buf[6]);
	printf("%c\n",buf[7]);
	
	sprintf(buf,"%06x",arg);
	printf("%s\n%d\n%d\n",buf,strlen(buf),sizeof(buf));
	printf("%c\n",buf[0]);
	printf("%c\n",buf[1]);

	printf("%c\n",buf[2]);
	printf("%c\n",buf[3]);
	printf("%c\n",buf[4]);
	printf("%c\n",buf[5]);
	printf("%c\n",buf[6]);
	printf("%c\n",buf[7]);
*/
}
