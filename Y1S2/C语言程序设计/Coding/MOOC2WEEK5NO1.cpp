#include<stdio.h>

int main(){
	int A[20]={0};
	int *p,sum=0,n;
	p = A ;
	for(int i=0;i<12;i++){
		scanf("%d",&A[i]);
	}
	scanf("%d",&n);
	for(int i=0;i<4;i++){
		printf("%d",*(p+(n-1)*4+i));
		if(i!=3) printf(" ");
		sum+=*(p+(n-1)*4+i);
	}
	printf("\n");
	printf("%g\n",sum/4.0);
}