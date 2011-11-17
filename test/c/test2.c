#include <stdio.h> 
#include <stdlib.h> 
#define N 100 
float f1(float x) 
{ 
       return (1+x*x); 
} 
float f2(float x) 
{ 
       return (1+x+x*x+x*x*x); 
} 
float f3(float x) 
{ 
       return(x/(1+x*x)); 
} 
float integral(float (*fun)(),float a,float b) 
{ 
       float s,h; 
       int i; 
       s=((fun)(a)+(fun)(b))/2.0;/* 这一步报错，不知道为什么*/ 
       h=(b-a)/N; 
       for(i=1;i<N;i++) 
       s+=(fun)(a+i*h); 
       return s*h; 
} 
int main() 
{ 
     float y1,y2,y3; 
     y1=integral(f1,0.0,1.0); 
     y2=integral(f2,0.0,2.0); 
     y3=integral(f3,0.0,3.5); 
     printf("y1=%6.2f\ny2=%6.2f\ny3=%6.2f\n",y1,y2,y3); 
     exit(0);
}
