#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int
cmpstringp(const void *p1, const void *p2)
{
    /* The actual arguments to this function are "pointers to
       pointers to char", but strcmp(3) arguments are "pointers
       to char", hence the following cast plus dereference */

   // return strcmp(* (char * const *) p1, * (char * const *) p2);
//	return strcmp(* (const char **) p1, * (const char **) p2);
return strcmp(* (char const **) p1, * (char const **) p2);
}

int
main(int argc, char *argv[])
{
    int j;

    if (argc < 2) {
     fprintf(stderr, "Usage: %s <string>...\n", argv[0]);
     exit(EXIT_FAILURE);
    }
printf("%d\n",sizeof(argv[1]));
printf("%d\n",sizeof(argv[2]));
printf("%d\n",sizeof(argv[3]));
printf("%d\n",sizeof(argv[4]));
     qsort(&argv[1], 0, sizeof(argv[1]), cmpstringp);

     for (j = 1; j < argc; j++)
         puts(argv[j]);
     printf("%d\n",sizeof("abc"));
     printf("%d\n",sizeof("abcd"));
     printf("%d\n",sizeof("abcde"));
     exit(EXIT_SUCCESS);
 }

