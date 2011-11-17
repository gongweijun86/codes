#include "stdio.h"  
#include "stdlib.h"  
#define N 5  
typedef struct BSTnode   
{  
    int key;  
    struct BSTnode *lchild,*rchild;  
}BSTnode,*BSTree;  

bool SearchBST(BSTree T,int key,BSTree f,BSTree &p)  
{  
    if (!T)   
    {  
        p=f;  
        return false;  
    }  
    else if (key==T->key)   
    {  
        p=T;  
        return true;  
    }  
    else if (key<T->key)   
    {  
        return SearchBST(T->lchild,key,T,p);  
    }  
    else  
        return SearchBST(T->rchild,key,T,p);  
}  
bool InsertBST(BSTree &T,int e)  
{  
    BSTnode* s,*p;  
    if (!SearchBST(T,e,NULL,p))   
    {  
        s=(BSTnode*)malloc(sizeof(BSTnode));  
        s->key=e;  
        s->lchild=NULL;  
        s->rchild=NULL;  
        if (!p)   
        {  
            T=s;  
        }  
        else if (e<p->key)   
        {  
            p->lchild=s;  
        }  
        else  
            p->rchild=s;  
        return true;  
    }  
    else  
        return false;  
}  
  
bool Delete(BSTree &p)  
{  
    BSTnode* q,*s;  
    if (!p->rchild)   
    {  
        q=p;  
        p=p->lchild;  
        free(q);  
    }  
    else if (!p->lchild)   
    {  
        q=p;  
        p=p->rchild;  
        free(q);  
    }  
    else  
    {  
        q=p;  
        s=p->lchild;  
        while (s->rchild)   
        {  
            q=s;  
            s=s->rchild;  
        }  
        p->key=s->key;  
        if (q!=p)   
        {  
            q->lchild=s->lchild;  
        }  
        else  
            q->lchild=s->lchild;  
        free(s);  
    }  
    return true;  
}  
  
bool DeleteBST(BSTree &T,int key)  
{  
    if (!T)   
    {  
        return false;  
    }  
    else  
    {  
        if (key==T->key)   
        {  
            return Delete(T);  
        }  
        else if (key<T->key)   
        {  
            return DeleteBST(T->lchild,key);  
        }  
        else return DeleteBST(T->rchild,key);  
    }  
}  
  
void CreateTree(BSTree &root,int data[])  
{  
    BSTree p;  
    BSTree current;  
    BSTree father;  
    int i;  
    for(i=0;i<N;i++)  
    {  
        p=(BSTnode*)malloc(sizeof(BSTnode));  
        p->key=data[i];  
        p->lchild=NULL;  
        p->rchild=NULL;  
        if (root==NULL)   
        {  
            root=p;  
        }  
        else  
        {  
            current=root;  
            while (current!=NULL)   
            {  
                father=current;  
                if (current->key>data[i])   
                {  
                    current=current->lchild;  
                }  
                else  
                    current=current->rchild;  
            }  
            if (father->key>data[i])   
            {  
                father->lchild=p;  
            }  
            else  
                father->rchild=p;  
        }  
          
    }  
}  
void InOrderBSTree(BSTree T)  
{  
    if (!T)   
    {  
        return;  
    }  
    else  
    {  
        InOrderBSTree(T->lchild);  
        printf("%d ",T->key);  
        InOrderBSTree(T->rchild);  
    }  
}  

BSTree proot;

int main(void)  
{  
    BSTree root=NULL;  
    BSTree p;  
    int data[N];  
    int key;  
    printf("input the data of the tree:\n");  
    for(int i=0;i<N;i++)  
    {  
        scanf("%d",&data[i]);  
    }  
    CreateTree(root,data);  

    proot = root;

    InOrderBSTree(root);  
    printf("\n");  
  
  
    printf("input the key value to search:\n");  
    scanf("%d",&key);  
    if (SearchBST(root,key,NULL,p))   
    {  
        printf("fouded!\n");  
    }  
    else  
        printf("Not found!\n");  
  
  
    printf("input the key value to insert:\n");  
    scanf("%d",&key);  
    InsertBST(root,key);  
    InOrderBSTree(root);  
    printf("\n");  
      
  
    printf("input the key value to delete:\n");  
    scanf("%d",&key);  
    DeleteBST(root,key);  
    InOrderBSTree(root);  
    printf("\n");  
      
}  
