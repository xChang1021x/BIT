#include<stdio.h>

int main(){
	int A[100]={0};
	int max;
	for(int i=0;i<10;i++){
		scanf("%d",&A[i]);
		if(i==0) max=A[0];
		else if(max<A[i]) max=A[i];
	}
	for(int i=0;i<10;i++){
		if(A[i]==max){
			printf("%d\n",i+1);
		}
	}
	return 0;
}