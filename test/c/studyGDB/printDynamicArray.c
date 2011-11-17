#include <stdlib.h>

int *x;

int main(void)
{
	x = (int *) malloc(25 * sizeof(int));
	x[3] = 12;
}
