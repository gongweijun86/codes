#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct Node
{
	int data;
	struct Node *next;
};

struct List
{
	struct Node *head;
};

void insert(struct List *plist, struct Node *node)
{
	node->next = plist->head->next;
	plist->head->next = node;
}

void reverse(struct List *plist)
{
	struct Node *head = plist->head;
	struct Node *s;
	struct Node *q;
	struct Node *t;
	s = head->next;
	t = q = s->next;
	s->next = NULL;
	while(t != NULL)
	{
		t = q->next;
		q->next = s;
		s = q;
		q = t;
	}

	plist->head->next = s;
}

int main(void)
{
	struct List list;
	struct List *plist;
	plist = &list;
	plist->head = (struct Node *)malloc(sizeof(struct Node));
	plist->head->next = NULL;
	plist->head->data = 0;

	struct Node *node1 = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node2 = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node3 = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node4 = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node5 = (struct Node *)malloc(sizeof(struct Node));

	node1->data = 1;
	node2->data = 2;
	node3->data = 3;
	node4->data = 4;
	node5->data = 5;

	insert(plist, node1);
	insert(plist, node2);
	insert(plist, node3);
	insert(plist, node4);
	insert(plist, node5);
	
	struct Node *p = plist->head->next;
	int i = 0;
	while(p != NULL)
	{
		printf("node%d:%d\n",++i,p->data);
		p = p->next;
	}

	reverse(plist);

	p = plist->head->next;
	i = 0;
	while(p != NULL)
	{
		printf("node%d:%d\n",++i,p->data);
		p = p->next;
	}
	reverse(plist);

	p = plist->head->next;
	i = 0;
	while(p != NULL)
	{
		printf("node%d:%d\n",++i,p->data);
		p = p->next;
	}
}
