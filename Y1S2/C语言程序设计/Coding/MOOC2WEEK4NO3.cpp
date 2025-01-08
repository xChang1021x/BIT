#include<stdio.h>

int main(){
	int A[20]={0};
	int *p = A;
	int x;
	for(int i=0;i<10;i++){
		scanf("%d",&A[i]);
	}
	scanf("%d",&x);
	for(int i=0;i<10;i++){
		if(*(p+i)==x){
			printf("%d\n",x);
			p = NULL;
			break;
		} 
	}
	if(p != NULL) printf("No\n");
}