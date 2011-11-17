#include "stdio.h"


/*#define Str(x) #x*/
/*#define Xstr(x) Str(x)*/
#define Xstr(x) #x
#define OP plus

/*#define TRACE(var, fmt) printf("TRACE: var = fmt\n", var)*/

#define TRACE(var, fmt) printf("TRACE: " #var "="  #fmt"\n", var)

int 
main()
{
	int i = 9;
	printf("%s\n",Xstr(OP));
	TRACE(i,%d);
	printf("this is ""a macros test""i=""%x""\n",i);
}

