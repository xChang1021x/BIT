#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct sdata  
{  int num;  
   struct sdata *next;  
} ;  
typedef struct sdata SNODE;  
void movenode( SNODE *, int );  
  
void setlink( SNODE * head, int n )  
{     
    SNODE *p;  
  
    while ( n > 0 )  
    {   p = ( SNODE * ) malloc( sizeof( SNODE ) );  
        p->num = n;  
        p->next = head->next;  
        head->next = p;  
        n --;  
    }  
}  
  
void outlink( SNODE * head )  
{  
    while( head->next != NULL )  
    {  
        head = head->next;  
        printf( "%d,", head->num );  
    }  
    return;  
}  
  
int main( )  
{   int n, m;  
    SNODE * head = NULL;  
  
    scanf("%d%d", &n, &m );  
    head = ( SNODE * ) malloc( sizeof( SNODE ) );  
    head->num = -1;  
    head->next = NULL;  
    setlink( head, n );  
  
    movenode( head, m ); 
  
    outlink( head );  
    printf("\n");  
    return 0;  
}  

void movenode( SNODE *h, int m ){
	SNODE *p;
	SNODE *n;
	
	p=h;
	int l=0;
	while(p->next){
		p=p->next;
		l++;
	}
	p=h;
	if(!(m>l||m==0||m==1))
	while(p->next->num!=m){
		p=p->next;
	}
	n=p->next;
	p->next= n->next;
	
	n->next=h->next;
	h->next=n;	
}