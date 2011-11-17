#include <stdio.h>
#include <stdint.h>

 void
 set_value( uint64_t* c, 
            uint32_t  a_val, 
            uint16_t  b_val ) 
 {
   uint32_t* a = (uint32_t*)c;
   uint16_t* b = (uint16_t*)c;
   
   a[0] = a_val; // < Address of c + 0
   b[2] = b_val; // < Address of c + 4
   b[3] = b_val; // < Address of c + 6
   
   // WHAT VALUE THIS WOULD PRINT IS UNDEFINED
   printf("c = 0x%08x\n", c[0] ); 
 }
int 
main(void)
{
	uint64_t c = 0x1234567812345678;
	uint32_t a;
	uint16_t b;
	set_value(&c,b,a);
}
