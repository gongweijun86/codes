//#include <iostream> 
#include <stdio.h>
int main(int argc, char* argv[])
{
	unsigned int test = 0x80000000; 
	unsigned int *pui = &test; 
//	int *pi = (int *)&test; 
//	float *pf = (float *)&test; 
	int *pi = (int *) &test; 
        float *pf = (float *) &test; 

//	std::cout << pui << '\t' << pi << '\t'   
//	<< pf << std::endl; 
//	std::cout << *pui << '\t' << *pi << '\t'   
//	<< *pf << std::endl;

	printf("pui=%x, pi=%x,pf=%x\n",pui, pi, pf);
	printf("*pui=%x,*pi=%x,*pf=%lf\n",*pui,*pi,*pf);
}

