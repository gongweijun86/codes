#include <stdio.h>

void foo(int* v1, int* v2, int* result, int count)
{
//int temp = *v1 + *v2; //3 + 4
    while(count--) {
 //*result = *result + temp;
// a = a + 7
	
        *result += (*v1 + *v2);
	//*result += (*v1 + *v2);
    }
}

int main(void)
{
	int a = 3;
	int b = 4;
	int r = 0;
	foo(&a,&b,&a,2);
	printf("a:%d\tb:%d\tr:%d\n",a,b,r);
}
// 3
//
//
