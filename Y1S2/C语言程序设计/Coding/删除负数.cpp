#include <stdio.h>  
#include <stdlib.h>  

struct node    
{  
    int data;    
    struct node * next;    
};    
    
typedef struct node NODE;   
typedef struct node * PNODE;  
   
PNODE constructlist( PNODE head, int num );  
void outlist( PNODE head );  
void deleteneg( PNODE head );   
    
int main ( )    
{   int num=1;    
    PNODE head;    
    
    head = (PNODE)malloc( sizeof(NODE) );    
    head->next = NULL;    
    head->data = -1;    
    
    while ( num!=0 )    
    {   scanf("%d", &num);    
        if ( num!=0 )    
           constructlist (head, num);    
    }    
    deleteneg( head );  
    outlist( head );    
    return 0;    
}    
    
PNODE constructlist( PNODE head, int num )  
{   PNODE p;  
    p = (PNODE)malloc( sizeof(NODE) );   
    p->data = num; 
    p->next = head->next;   
    head->next = p;  
    return head;  
}  
  
void outlist( PNODE head )    
{   PNODE p;    
    p = head->next;    
    while ( p != NULL )    
    {   printf("%d\n", p->data);    
        p = p->next;    
    }    
}    
    
void deleteneg(PNODE head)
{
    PNODE p,temp1,temp2;         
    p = head; 
    int flag = 0;
    while ( p->next != NULL )         
    {   
    	temp1 = p -> next;
        while( temp1->data <= 0)
		{
			p->next = temp1->next;
			free(temp1);
			temp1 -> data= 2;
			if(p ->next !=NULL)
			temp1 = p -> next;
        }
        if(p ->next !=NULL)
        p = p -> next;
    } 
    
}