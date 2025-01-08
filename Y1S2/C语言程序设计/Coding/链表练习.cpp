#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
}NODE;

NODE* createList()
{
	NODE* headNode = (NODE*)malloc(sizeof(NODE));
	headNode -> next = NULL;
	return	headNode;
}

NODE* createNode(int data)
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode -> data = data;
	newNode -> next = NULL;
	return newNode;
}

void insertNewNode(NODE* headNode, int data)
{
	NODE* newNode = createNode(data);
	newNode -> next = headNode -> next; 
	headNode -> next = newNode;
	headNode -> data = data;
}

void deleteNode(NODE* headNode, int n)
{
	NODE* pMove = headNode;
	while()
	{
		
	}
}

void printList(NODE* headNode)
{
	NODE* pMove = headNode -> next;
	while(pMove)
	{
		printf("%d ",pMove->data);
		pMove = pMove -> next;
	}
	printf("\n");
}

int main()
{
	struct Node* headNode;
	int data;
	scanf("%d",&data);
	headNode = createList();
	headNode -> next = createNode(data);
	for(int i=0;i<10;i++){
		insertNewNode(headNode,i);	
	}
	printList(headNode);
	return 0;
}