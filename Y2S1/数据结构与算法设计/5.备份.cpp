/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>
typedef struct node
{   int         data;
    struct node * next;
} NODE;

NODE * find( NODE * , int * );
void outputring( NODE * );
void change( int , int , NODE * );
void outputring( NODE * pring )
{	NODE * p;
	p = pring;
	if ( p == NULL )
		printf("NULL");
	else
		do	{	printf("%d", p->data);
			p = p->next;
		} while ( p != pring );
	printf("\n");
	return;
}

int main()
{   int n, m;
	NODE * head, * pring;

	scanf("%d%d", &n, &m);
	head = (NODE *)malloc( sizeof(NODE) );
	head->next = NULL;
	head->data = -1;

	change( n, m, head );
	pring = find( head, &n );
	printf("ring=%d\n", n);
	outputring( pring );

	return 0;
}

void change(int n, int m, struct node * head){
	NODE* q = head;
	int History[10000] = {0};
	int x = 0, flag = 0;
	for (int i = 0; i < 10000; i++){
		History[i] = -1;
	}
	while (m % 10 == 0){
		if (n % 10 == 0){
			n /= 10;
		}
		m /= 10;
	}
	while (1){
		NODE* p = (NODE *)malloc( sizeof(NODE) );
		p->data = (n*10)/m;
		p->next = NULL;
		q->next = p;
		if ((n*10) % m == 0){
			break;
		}
		for (int i = 0; i < x; i++){
			if (History[i] == (n*10) % m){
				NODE* r = head->next;
				while (i--){
					r = r->next;
				}
				if (p->data != r->data){
					p->next = r->next;
					r->next->data -= 10;
				}
				else{
					q->next = r;
					r->data -= 10;
				}
				
				flag = 1;
				break;
			}
		}	
		if (flag)
			break;
		q = q->next;
		History[x++] = (n*10) % m;
		n = (n*10) % m;
	}
}

NODE * find( NODE * head, int * n )
{
	NODE* p = head->next;
	NODE* q = head->next;
	int x = 0, y = 0;
	do {
		if (p == NULL || p->next == NULL){
			*n = 0;
			return NULL;
		}
		p = p->next;
		if (p->data < 0){
			x++;
			if (x == 2){
				p->data += 10;
				break;
			}
			y = 0;
		}
		y++;
	} while (1);
	
	*n = y;
	return p;
}


/* PRESET CODE END - NEVER TOUCH CODE ABOVE */