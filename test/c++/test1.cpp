#include <iostream> 
#include <vector> 
#include <string> 
  
using namespace std; 
  
int main(){ 
  
     vector<string*> pstr; 
     string sval; 
     while(cin>>sval){ 
          string *p=new string;//string *p不属于重复定义么？ 
          *p = sval; 
          pstr.push_back(p); 
          delete p;//为什么p不能删？去掉这一行和下面一行就正常了，不去掉就在运行时出错。 
          p=NULL; 
     } 
     cout<<"Input finished!"<<endl; 
	      
     for(vector<string*>::iterator iter = pstr.begin();iter!=pstr.end();++iter) 
          cout<<**iter<<endl; 
//	   
     return 0; 
}
