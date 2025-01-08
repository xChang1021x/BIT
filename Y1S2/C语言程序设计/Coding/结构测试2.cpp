#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct numLink  
{  
    int no;  
    struct numLink *next;  
}NODE;  
  
void movenode( NODE *head);  
  
void SetLink( NODE *h, int n )  
{  
    NODE *p=NULL, *q=NULL;  
    int i;  
    for( i=0; i<n; i++)  
    {  
        p = (NODE *)malloc(sizeof(NODE));  
        p->no = i+1;  
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
    int n;  
    NODE *head=NULL, *q=NULL;  
    scanf("%d",&n);  
  
    head = (NODE *)malloc(sizeof(NODE));  
    head->no = -1;  
    head->next = NULL;  
  
    SetLink( head, n );  
    movenode( head );  
  
    q = head;  
    while (q->next){  
        printf("%d ",q->next->no);  
        q = q->next;  
    }   
    printf("\n");  
      
    system("pause");  
    return 0;  
}  

void movenode( NODE * head)
{
	head = head->next;
	NODE *move,*save;
	save = (NODE *)malloc(sizeof(NODE));
	move = (NODE *)malloc(sizeof(NODE));
	move = head->next;
	save = head->next;
	while(head->next->next != NULL && head->next != NULL)
	{
		if(move->next->next != NULL)
		{
			head->next = head->next->next;
			head = head->next;
			move->next = move->next->next;
			move = move->next;
		}
		else
		{
			head->next = head->next->next;
			head = head->next;
			move->next = move->next->next;
			head->next = save;
			return;
		}
	}
	if(head->next == NULL || head->next->next == NULL)
	{
		head->next = save;
	}
	save = NULL;
	move = NULL;
	return;
}