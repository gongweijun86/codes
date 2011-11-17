#include <iostream>
using namespace std;

void WorkingMethod(int *& i)
{
	i = new int();
	*i = 3;
}


void NotWorkingMethod(int* i)
{
	i=new int;
	*i=3;
}

int main(int argc, char* argv[])
{
	int* i1=NULL;
	WorkingMethod(i1);
	cout<<"i1="<<*i1<<endl;

	int* i2=NULL;
	NotWorkingMethod(i2);
	cout<<"i2="<<*i2<<endl; //Will crash here
}
