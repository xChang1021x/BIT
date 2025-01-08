#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
	char name[20];
	struct node *link;
};

typedef struct node NODE;
void create(NODE *head){
	NODE *p;
	char name[20];
	int flag = 1;
	do{
		gets(name);
		if(strlen(name)==0)
			flag = 0;
		else{
			p = (NODE*)malloc(sizeof(NODE));
			strcpy(p -> name, name);
			p -> link = head -> link;
			head -> link = p;
		}
	}
	while(flag);
}

void output(NODE *head){
	NODE *p;
	p = head -> link;
	while(p != NULL){
		puts(p->name);
		p = p -> link;
	}
}

int main(){
	NODE *head;
	head = (NODE*)malloc(sizeof(NODE));
	head -> link = NULL;
	create(head);
	output(head);
	return 0;
}