#include <stdio.h>  
#include <stdlib.h>  

struct Node {  
    char *name;  
    int  score;  
    struct Node *next;  
};  

struct Node *  connect(struct Node *x, struct Node *y, struct Node *z);  
  
int main(int argc, char *argv[]) {      
    struct Node a, b, c, *p;     
    a.name = "LiPing";  
    b.name = "LiuHai";  
    c.name = "FengYun";   
    scanf("%d,%d,%d", &a.score, &b.score, &c.score);  
    p= connect(&a,&b,&c);  
    printf("%s-%d\n",p->name,p->score);  
    p=p->next;  
    printf("%s-%d\n",p->name,p->score);  
    p=p->next;  
    printf("%s-%d\n",p->name,p->score);  
    return 0;  
}

struct Node *  connect(struct Node *x, struct Node *y, struct Node *z){
	struct Node *p, *q;

	
}