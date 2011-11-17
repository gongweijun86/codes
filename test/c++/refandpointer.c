#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct __Node
{
	int data;
	__Node *left;
	__Node *right;	
}Node;

Node root,child1,child2,child3,child4;

void func(Node* &p)
{
	Node* &q = p;
	p = p->left;
	//free(q);
	cout << p->data << endl;
	cout << root.right->data << endl;
}

int main(void)
{
	root.data = 0;
	root.left = &child1;
	root.right = &child2;

	child1.data = 1;
	child1.left = NULL;
	child1.right = NULL;

	child2.data = 2;
	child2.left = &child3;
	child2.right = NULL;

	child3.data = 3;
	child3.left = NULL;
	child3.right = &child4;

	child4.data = 4;
	child4.left = NULL;
	child4.right = NULL;

	Node *pp = &child2;
	func(pp);
}
