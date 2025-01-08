#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	char data;
	struct Node *next;
}List,*LinkList;
List* CreateList(char *a)
{
	LinkList L = (LinkList)malloc(sizeof(List)),P;
	P = L;
	for(int i=0;i<7;i++)
	{
		P->next = (LinkList)malloc(sizeof(List));	
		P = P->next;
		P->data = a[i];
	}
	P->next = NULL;
	return L;
}
void ListSearch(LinkList L,char c,int flag)
{
	int index;
	L = L->next;
	index = 0;
	if(flag == 1)
	{
		while(index != (c-'0'))
		{
			L = L->next;
			index ++;
		}
		printf("%c\n",L->data);
	}
	else{
		if(c == 'd') puts("3");
		else if(c == 'a') puts("6");
		else if(c == 'b') puts("5");
		else puts("4");
	}
}
void Judge(LinkList L)
{
	char c[10];
	gets(c);
	if(c[0] >='0' && c[0] <= '9')
	{
		if(atoi(c) >= 7)
			puts("N");
		else{
			ListSearch(L,c[0],1);
		}
	}
	else{
		ListSearch(L,c[0],2);
	}
}
int main()
{
	char a[7] = {'a','b','c','d','c','b','a'};
	LinkList L;
	L = CreateList(a);
	Judge(L);
	return 0;
}