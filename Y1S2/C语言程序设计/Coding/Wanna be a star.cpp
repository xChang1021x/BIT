#include<stdio.h>

int main(){
	int max,min,sum=0;
	int A[15]={0};
	for(int i=0;i<10;i++){
		scanf("%d",&A[i]);
	}
	max=A[0];
	min=A[0];
	for(int i=1;i<10;i++){
		if(max<A[i]) max=A[i];
		if(min>A[i]) min=A[i];
	}
	for(int i=0;i<10;i++){
		if(A[i]==max){
			A[i]=0;
			break;
		}
	}
	for(int i=0;i<10;i++){
		if(A[i]==min){
			A[i]=0;
			break;
		}
	}
	for(int i=0;i<10;i++){
		sum+=A[i];
	}
	printf("Canceled Max Score:%d\n",max);
	printf("Canceled Min Score:%d\n",min);
	printf("Average Score:%d\n",sum/8);
	return 0;
}