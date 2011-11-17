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
	struct Node *tail;
};

void insert(struct List *plist, struct Node *node)
{
	node->next = plist->head;
	plist->head = node;
	if (plist->tail == NULL)
	{
		plist->tail = node;
	}
}

void reverse(struct List *plist)
{
	struct Node *head = plist->head;
	struct Node *tail = plist->tail;
	struct Node *s;
	struct Node *t;
	s = head;
	t = s->next;
	head = NULL;
	while(head != tail)
	{
		s->next = head;
		head = s;
		if (t != NULL)
		{
			s = t;
			t = s->next;
		}
	}

	plist->tail = plist->head;
	plist->head = head;
}

int main(void)
{
	struct List list;
	struct List *plist;
	plist = &list;
	plist->head = NULL;
	plist->tail = NULL;

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
	
	struct Node *p = plist->head;
	int i = 0;
	while(p != NULL)
	{
		printf("node%d:%d\n",++i,p->data);
		p = p->next;
	}

	reverse(plist);

	p = plist->head;
	i = 0;
	while(p != NULL)
	{
		printf("node%d:%d\n",++i,p->data);
		p = p->next;
	}

	reverse(plist);

	p = plist->head;
	i = 0;
	while(p != NULL)
	{
		printf("node%d:%d\n",++i,p->data);
		p = p->next;
	}

	reverse(plist);

	p = plist->head;
	i = 0;
	while(p != NULL)
	{
		printf("node%d:%d\n",++i,p->data);
		p = p->next;
	}


}
