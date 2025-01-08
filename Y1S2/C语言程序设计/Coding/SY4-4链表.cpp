/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>
typedef struct numLink
{
	int no;
	struct numLink *next;
}NODE;

NODE *MoveNode( NODE * );

void SetLink( NODE *h )
{
	NODE *p=NULL, *q=NULL;
	int m;
	while(1)
	{
		scanf("%d",&m);
		if( m == -1 )
			return ;
		p = (NODE *)malloc(sizeof(NODE));
		p->no = m;
		p->next = NULL;
		if( h->next == NULL )
		{
			h->next = p;
			q = p;
		}
		else
		{
			q->next = p;
			q = q->next;
		}
	}
	return;
}

int main( )
{
	NODE *head=NULL, *q=NULL;
	head = (NODE *)malloc(sizeof(NODE));
	head->no = -1;
	head->next = NULL;

	SetLink( head );
	q = MoveNode( head );
	do
	{
		printf("%d ",q->next->no);
		q = q->next;
	}while( q->next != NULL ); 
	printf("\n");
	return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */


NODE* MoveNode( NODE *head)    
{    
    NODE *p, *q, *r,*pend;    
    p = head;
	pend = head;
    while(pend->next != NULL)
    {
    	pend = pend -> next;
	}
	r = pend;
	while(p -> next != pend)
	{
		if(p -> next -> no % 2 ==0)
		{
			q = p -> next;
			r -> next = q;
			r = r -> next;
			p -> next = p -> next -> next;
			q -> next = NULL;
		}
		else p = p -> next;
	}
	if(pend -> no % 2 == 0)
	{
		r -> next = pend;
		p -> next = p -> next -> next;
		pend -> next = NULL;
	}
	return head;
}