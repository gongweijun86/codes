#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#define va_arg(ap,t)    ( ((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )

#include <stdlib.h>
#include <stdio.h>

int 
main(int argc,char *argv)
{
    int ap = 2;
    int l = va_arg(ap,0);

    printf ( "%d\n",ap );
    printf ( "%d\n",l );

}
