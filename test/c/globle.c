#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "globle1.h"
typedef struct
{
	int a;
	char b;
}A;

A *t;

void init()
{
    t->a=9090;
    t->b='w';
}

int
main(int argc,char **argv)
{
    t = (A *)malloc(sizeof(A));
    t->a=123;
    t->b='a';
    printf("%d",t->a);
    printf("%c",t->b);
    t->a=999;
    t->b='g';
    init();
    test();
    printf("%d",t->a);
    printf("%c",t->b);
    return 0;
}
