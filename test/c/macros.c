#include <stdio.h>

#define min(x,y) (x<y?x:y)

#define	STRING(x) #x			/*  */

#define	SIGN(x) INT_##x

#define	TEST(x) (x + TEST(x))			/*  */

#define	PARAM(x)  #x
/*  */
#define	ADDPARAM(x) INT_##x			/*  */

#define	TO_STRING(x) TO_STRING1(x)			/*  */

#define	TO_STRING1(x) #x			/*  */
int main(int argc,char* argv)
{
    printf("%d",min(3,4));  
    const char* str = STRING(test_string);
    printf("\n"); 
    printf(str);
    printf("\n"); 
    int SIGN(2);
    SIGN(2)= 4;
    printf("%d",INT_2);    
    printf("\n"); 
/*
 * gcc -gdwarf-2 -g3 test.c -o test
 * gdb -nw test
 * 查看宏展开
 */
}
