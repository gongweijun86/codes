#include <stdio.h>

/*char*s="char*s=%c%s%c;main(){printf(s,34,s,34);}";*/
/*    main(){printf(s,34,s,34);}*/

#define q(k)main(){return!puts(#k"\nq("#k")");}
    q(#define q(k)main(){return!puts(#k"\nq("#k")");})


