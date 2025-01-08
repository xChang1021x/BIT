#include<stdio.h>

int main(){
	int A[20]={0};
	int *p,temp;
	for(int i=0;i<10;i++){
		scanf("%d",&A[i]);
	}
	p = A;

	for(int i=0;i<9;i++){
		for(int j=i+1;j<10;j++){
			if(*(p+i) > *(p+j)){
				temp = *(p+i);
				*(p+i) = *(p+j);
				*(p+j) = temp;
			}
		}
	}
	for(int i=0;i<10;i++){
		printf("%d",*(p+i));
		if(i!=9) printf(",");	
	}
	printf("\n");
}