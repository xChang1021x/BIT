/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{   int    coef, exp;
    struct node  *next;
} NODE;

void multiplication( NODE *, NODE * , NODE * );
void input( NODE * );
void output( NODE * );

void input( NODE * head )
{   int flag, sign, sum, x;
	char c;

    NODE * p = head;

	while ( (c=getchar()) !='\n' )
	{
		if ( c == '<' )
	    {    sum = 0;
	         sign = 1;
	         flag = 1;
        }
		else if ( c =='-' )
             sign = -1;
		else if( c >='0'&& c <='9' )
		{    sum = sum*10 + c - '0';
        }
		else if ( c == ',' )
        {    if ( flag == 1 )
             {    x = sign * sum;
                  sum = 0;
                  flag = 2;
		  sign = 1;
             }
        }
		else if ( c == '>' )
        {    p->next = ( NODE * ) malloc( sizeof(NODE) );
             p->next->coef = x;
             p->next->exp  = sign * sum;
             p = p->next;
             p->next = NULL;
             flag = 0;
        }
    }
}

void output( NODE * head )
{
    while ( head->next != NULL )
    {   head = head->next;
        printf("<%d,%d>,", head->coef, head->exp );
    }
    printf("\n");
}

void multiplication( NODE *h1, NODE *h2, NODE *h3){
	NODE *p = h1->next, *q = h2->next, *r = h3, *after = h3;
	NODE *record;
	int pre=0, flag2 = 1;
	while (1){
		NODE *s = (NODE *)malloc(sizeof(NODE));
		s->coef = p->coef * q->coef;
		s->exp = p->exp + q->exp;
		s->next = NULL;
		h3->next = s;
		if (q->next != NULL){  
	        q = q->next;  
	    }  
	    else if (p->next != NULL){  
	        p = p->next;
	        q = h2->next;
	    }  
	    else{
	    	if (s->coef == 0){
				s->exp = 0;
			}
	        return;  
	    }
	    
	    if (s->coef != 0){
	   		after = h3;
			pre = s->exp;	
			break;
		}
			
	}
	
	while(p != NULL){
		int flag = 1;  
        NODE *t = (NODE *)malloc(sizeof(NODE));  
        t->coef = q->coef * p->coef;  
        t->exp = q->exp + p->exp;  
        t->next = NULL;  
		r = after;
              
        if (t->coef != 0){
	        while (r->next != NULL){  
	            if (r->next->exp == t->exp){  
	                r->next->coef += t->coef;  
	                if (r->next->coef == 0){  
	                    NODE *pdelete = r->next;  
	                    flag = 0;  
	                    if (r->next->next != NULL)  
	                        r->next = r->next->next;  
	                    else  
	                        r->next = NULL;  
	                          
	                    free(pdelete);  
	                }  
	                break;  
	            }  
	            else if (r->next->exp > t->exp){  
	                t->next = r->next;  
	                r->next = t;  
	                break;  
	            }  
	            else{  
	                r = r->next;  
	            }  
	        }
			if (flag2){
				record = r;
				flag2 = 0;
			}  	
		}
		
        if (r->next == NULL && flag){  
            r->next = t;  
        }  
        if (q->next == NULL){
        	flag2 = 1;
        	int time = p->exp - pre;
            after = record;
			q = h2;  
			pre = p->exp;
            p = p->next;
        }  
        q = q->next;
			
	}
}

int main()
{   NODE * head1, * head2, * head3;

    head1 = ( NODE * ) malloc( sizeof(NODE) );
    input( head1 );

    head2 = ( NODE * ) malloc( sizeof(NODE) );
    input( head2 );

    head3 = ( NODE * ) malloc( sizeof(NODE) );
    head3->next = NULL;
    multiplication( head1, head2, head3 );

	output( head3 );
	return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */