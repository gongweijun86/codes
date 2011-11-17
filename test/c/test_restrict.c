#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void f(const int* pci, int* pi)
{
	(*pi) += 1;
	*pi = (*pci) + 2;
}


int main(int argc, char* argv[])
{
	int n = 3;
	f(&n, &n);
	printf("%d\n",n);
}

