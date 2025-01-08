#include<stdio.h>

int main(){
	int A[100][100]={0};
	int m,n;
	while(~scanf("%d %d",&m,&n)){
		int panduan=0;
		int max,min,row=0,col=0;
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				scanf("%d",&A[i][j]);
			}
		}
		for(int i=0;i<m;i++){
			max=A[i][0];
			for(int j=0;j<n;j++){
				if(max<A[i][j]){
					max=A[i][j];
					col=j;
				}
			}
			min=A[0][col];
			for(int k=0;k<m;k++){
				if(min > A[k][col]){
					min=A[k][col];
					row=k;
				}
			}
			if(max==min){
				printf("Point:a[%d][%d]==%d\n",row,col,max);
				break;
			}
		}
		if(max!=min){
			printf("No Point\n");
		}
	}
}