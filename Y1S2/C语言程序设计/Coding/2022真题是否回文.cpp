/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

//构造结构体
typedef struct list
{
	char data;
	struct list *next;
}*List,LNode;

//函数声明
List init_list(List head);
int chkPalindrome(List head);

int main()
{
	List head;	
	head = (LNode*)malloc(sizeof(LNode));	
	head->next = NULL;
	head = init_list(head);	
	if(chkPalindrome(head))	
		printf("单链表中有回文结构!\n");	
	else	
		printf("单链表中无回文结构!\n");

}

//链表初始化函数
List init_list(List head)
{
	int i = 0;	
	List p = head;	
	
	char chain[1000];
	memset(chain, 0, 1000 * sizeof(char));
	gets(chain);
		
	while(chain[i]!='\0')	
	{	
		List s;		
		s = (LNode*)malloc(sizeof(LNode));		
		s->data = chain[i];		
		s->next = NULL;		
		p->next = s;		
		p = p->next;		
		i++;		
	}	
	return head->next;	
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

int chkPalindrome(List head)
{
	if(head == NULL) return 1;
	int sum=1,x=0,y=0;
	char A[1000]={0};
	char B[1000]={0};
	List p = head ,q = head;
	while(q -> next != NULL)
	{
		sum++;
		q = q -> next;
	}
	y = sum/2 - 1;
	for(int i=0;i<sum;i++)
	{
		if(i<sum/2) A[x++] = p -> data;
		else if(sum%2==0) B[y--] = p -> data;
		else if(i!=sum/2) B[y--] = p -> data;

		p = p -> next;
	}
	if(strcmp(A,B)==0) return 1;
	else return 0;
}