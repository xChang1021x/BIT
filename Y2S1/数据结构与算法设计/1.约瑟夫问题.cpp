#include<iostream>
#include<algorithm>

using namespace std;

struct Node{
	int num;
	Node *next;
};

Node *head;
Node *p, *q, *r;
int n, k, m;

void createHead(){
	head = (Node *)malloc(sizeof(Node));
	head -> next = NULL;
	q = head;
}

void createList(){
	int x = k;
	for (int i = 0; i < n; i++){
		Node *p = (Node *)malloc(sizeof(Node));		
		p -> num = x++;
		q -> next = p;
		p -> next = NULL;
		q = p;
		if (x > n)
		 x -= n;
	}
	q -> next = head -> next;
}

int main(){
	int cnt = 0, cnt2 = 1;
	int max;
	scanf("%d,%d,%d", &n, &k, &m);
	max = n;
	if (n < 1 || m < 1 || k < 1){
		printf("n, k, m must bigger than 0.\n");
	}
	else if (k > n){
		printf("k should not bigger than n.\n");
	}
	else{
		createHead();
		createList();
		p = head -> next;
		q = head;
		while(n){
			if (cnt == m - 1){
				cnt = 0;
				
				printf("%d",p -> num);
				
				if (cnt2 % 10 == 0 || cnt2 == max){
					printf("\n");
				}
				else{
					printf(" ");
				}
				cnt2++;
				
				
				r = p;
				q -> next = p -> next;
				p = p -> next;
				free(r);
				n--;
				
			}
			else{
				cnt++;
				q = q -> next;
				p = p -> next;
			}
		}
	}
}