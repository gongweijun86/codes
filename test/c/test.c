#include <stdio.h>
#include <string.h>

int
main()
{
/*	int realarray[10]={1,2,3,4,5,6,7,8,9,0};*/
/*	int *array = &realarray[-1];*/
/*	printf("%d\n",array[1]);*/

	char answer[100], *p;
	printf("Type something:\n");
	fgets(answer, sizeof answer, stdin);
	if((p = strchr(answer, '\n')) != NULL)
	    *++p = '\0';
	//gets(answer);
	printf("You typed \"%s\"\n", answer);
	printf("%d\n",sizeof('a'));

	
}
