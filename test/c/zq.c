#include <stdio.h>
#include <string.h>

char *locate;

char *strtk(char x[1024],char *db,int i)
{
	char p[1024];
	int j;
	for(j=1;j<=i;j++)
	{
		locate=strstr(x,db);
		printf("%s\n",locate);
		sscanf(locate+1,"%s",p);
		printf("%s\n",locate);
		printf("p%s\n",p);
		memset(x,0,1023);
		printf("-%s\n",locate);
		strcpy(x,p);
		printf("p%s\n",p);
		printf("x%s\n",x);
		printf("--%s\n",locate);
	}
	printf("---%s\n",locate);
	return locate;
}


int main()
{
	char p1[1024];
	char buf[1024]="VIDEO-QAM-DEVICE-MIB::vqdInputPsiProgCaDescr.ipv4.'we23f'.1.3 = STRING: WQZ";

	char* l=strtk(buf,":",1);
	printf("%s\n",l);
	sscanf(l+1,"%s",p1);
	printf("VODName=%s\n",p1);

	return 0;
}


