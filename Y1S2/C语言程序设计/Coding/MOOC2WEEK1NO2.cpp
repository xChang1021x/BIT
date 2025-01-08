#include<stdio.h>

void arr(int A[20]){
	int temp,x;
	for(int i=0;i<8;i++){
		for(int j=i;j<9;j++){
			if(A[i]>A[j]){
				temp = A[i];
				A[i] = A[j];
				A[j] = temp;
			}
		}
	}
	scanf("%d",&x);
	for(int i=0;i<9;i++){
		if(x>A[i]) continue;
		else{
			for(int j=9;j>i;j--){
				A[j]=A[j-1];
			}
			A[i]=x;
			break;
		}
	}
}

int main(){
	int A[20]={0};
	for(int i=0;i<9;i++){
		if(i!=8) scanf("%d,",&A[i]);
		else scanf("%d",&A[i]);
	}
	arr(A);
	for(int i=0;i<10;i++){
		printf("%d",A[i]);
		if(i!=9) printf(",");
	}
	printf("\n");
}