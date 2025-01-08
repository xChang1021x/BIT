#include<stdio.h>

int main(){
	int A[5][5]={0};
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			scanf("%d",&A[i][j]);
		}
	}
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			printf("%d",A[j][i]);
			if(j!=2) printf(" ");
		}
		printf("\n");
	}
	return 0;
}