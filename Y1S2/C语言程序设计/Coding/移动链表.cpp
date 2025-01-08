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

void movenode( NODE *head)    
{    
    NODE *p, *q, *last;    
    p = head->next;    
    last = head;    
    int count = 0;    
    while (last->next != NULL)    
    {    
        last = last->next;    
        count ++;    
    }    
      
    for(int i=0;i < count/2 && count != 2; i ++)    
    {    
        q = p->next;    
        if (q->no % 2 == 0 )    
        {    
            p->next = q->next;    
            q->next = NULL;    
            last->next = q;    
            last = last->next;    
        }    
          
        p = p->next;    
    }    
}