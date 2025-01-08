#include "stdio.h"  
#include "stdlib.h"  

struct node  
{   int data;  
    struct node * next;  
} ;  
  
typedef struct node NODE;  
typedef struct node * PNODE;  
void outlist( PNODE );  
void sortlist( PNODE h, int num );
  
int main ( )  
{   int num=1;  
    PNODE head;  
  
    head = (PNODE)malloc( sizeof(NODE) );  
    head->next = NULL;  
    head->data = -1;  
  
    while ( num!=0 )  
    {   scanf("%d", &num);  
        if ( num!=0 )  
            sortlist( head, num);  
    }  
    outlist( head );  
    return 0;  
}  
  
void outlist( PNODE head )  
{   PNODE p;  
    p = head->next;  
    while ( p != NULL )  
    {   printf("%d\n", p->data);  
        p = p->next;  
    }  
}

void sortlist( PNODE h, int num ) 
{ 
    PNODE p,m;   
    p = ( PNODE )malloc( sizeof(NODE) );   
    p->data = num;	
	m = h;   
	
    while(m->next)
    {   
    	if(num<=m->data)   { break; }   
        m=m->next;   
    }   
    
    if(num == m->data)   
        { free(p); }  
    else if (num > m->data)  
        {   
            p->next = m->next; 
            m->next = p;   
        }   
        else if (num < m->data)   
        {   
            int temp;   
            temp = m->data;  
            m->data = num;   
            p->data = temp;  
			 
            p->next = m->next;   
            m->next = p;   
        }   
} 