#include <stdint.h>
#include <stdio.h>

uint32_t 
swap_words( uint32_t arg )
{
  char* const cp = (char*)&arg;
  const char  c0 = cp[0];
  const char  c1 = cp[1];
  const char  c2 = cp[2];
  const char  c3 = cp[3];

  cp[0] = c2;
  cp[1] = c3;
  cp[2] = c0;
  cp[3] = c1;
	printf("%x\n",cp[0]);
	printf("%x\n",cp[1]);
	printf("%x\n",cp[2]);
	printf("%x\n",cp[3]);

  return (arg);
} 
int main(void)
{
	uint32_t arg = 0x12345678;
	swap_words(arg);
	printf("arg:%x\n",arg);
}
