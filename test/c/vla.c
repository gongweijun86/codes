#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int i = atoi(argv[1]);
	int arr[i];
	for( int j=0; j < i; j++)
		arr[j] = atoi(argv[j+2]);
	for(int j=0; j < i; j++)
		printf("%d\t",arr[j]);
}

