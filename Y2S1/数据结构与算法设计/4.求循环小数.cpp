/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{   int         data;
    struct node * next;
} NODE;

void output( NODE *, int );
void change( int, int, NODE * );

void output( NODE * head, int kk )
{   int k=0;

	printf("0.");
	while ( head->next != NULL && k<kk )
	{   printf("%d", head->next->data );
		head = head->next;
		k ++;
	}
	printf("\n");
}
	
void change(int n, int m, struct node * head){
	NODE* q = head;
	int History[10000] = {0};
	int x = 0, flag = 0;
	while (1){
		NODE* p = (NODE *)malloc( sizeof(NODE) );
		p->data = (n*10)/m;
		p->next = NULL;
		if ((n*10) % m == 0){
			q->next = p;
			break;
		}
		for (int i = 0; i < x; i++){
			if (History[i] == (n*10) % m){
				NODE* r = head -> next;
				while (i--){
					r = r->next;
				}
				q->next = r;
				flag = 1;
				break;
			}
		}	
		if (flag)
			break;
		q->next = p;
		q = q->next;
		History[x++] = (n*10) % m;
		n = (n*10) % m;
	}
}

int main()
{   int n, m,k;
	NODE * head;

	scanf("%d%d%d", &n, &m, &k);
	head = (NODE *)malloc( sizeof(NODE) );
	head->next = NULL;
	head->data = -1;
	change( n, m, head );
	output( head,k );
	return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */