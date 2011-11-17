#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	struct line{
		int len;
		char s[0];
	};
	printf("%d\n",sizeof(struct line));
	struct line *l = (struct line*)malloc(sizeof(struct line) + 10);
	l->len = 123;
	l->s[0] = 0;
	l->s[1] = 1;
	l->s[2] = 2;
	l->s[3] = 3;
	l->s[4] = 4;
	l->s[9] = 9;
	l->s[10] = 10;
	int i;
	for(i = 0; i <= 41; i++)
	{
		printf("%d\n",l->s[i]);
	}
}

