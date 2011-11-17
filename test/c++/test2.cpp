#include <iostream>
#include <stdio.h>

using namespace std;

int main()   
{   
    string str1 = "abcd";   
    string str2 = str1;   
    printf("str1:%x str2:%x\n",&str1,&str2);
    char *p1 = const_cast<char*>(str1.c_str());   
    p1[0] = 'o';   
    //这里str1和str2同时被修改了   
    printf("%s %s\n", str1.c_str(), str2.c_str());   
    printf("str1:%x str2:%x\n",&str1,&str2);
    string str3 = "abcd";   
    string str4 = str3;   
    char *p2 = &(str3[0]);   
    p2[0] = 'o';   
    //这里只有str3被修改，str4不变   
    printf("%s %s\n", str3.c_str(), str4.c_str());   
    printf("str3:%x str4:%x\n",&str3,&str4);
    return 0;   
}
