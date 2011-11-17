#include <stdio.h>
#include <stdlib.h>

int
main(void){
	char* p = (char*)malloc(sizeof(char));
	char* q = p;
	if(q != NULL){
		printf("%x\n",q);
	}

}
