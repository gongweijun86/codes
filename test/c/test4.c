#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
char *get_a_day(int idx); 
static const char *msg[]={"sunday","monday","tuesday"}; 
char buf[20]; 
char *get_a_day(int idx) 
{    
       int i;
       for(i=0;i<20;i++) 
           buf[i]=0; 
       strcpy(buf,msg[idx]); 
       return buf; 
} 
int main() 
{ 
    char *buf1 = malloc(sizeof(char) * 20);
    char *buf2 = malloc(sizeof(char) * 20);
    buf1 = get_a_day(0);
    buf2 = get_a_day(1);
    //printf("%s  %s\n",get_a_day(0),get_a_day(1)); 
    printf("%s\n",buf1); 
    printf("%s\n",buf2); 

    //free(buf1);
    //free(buf2);
    return 0; 
}
