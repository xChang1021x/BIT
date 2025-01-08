#include<stdio.h>

int main(){
	int A[100][100]={0};
	int m,n;
	while(~scanf("%d %d",&m,&n)){
		int x=1,y=0;
		A[0][0]=m;
		for(int i=0;i<(n-1)*3;i++){
			if(i<n){
				A[0][y++]=m++;
				if(m>9) m-=10;
			}
			else if(i<2*n-1){
				A[x++][--y-1]=m++;
				if(m>9) m-=10;
			}
			else{
				A[--x-1][0]=m++;
				if(m>9) m-=10;
			}
		}
		for(int i=0;i<n;i++){
			for(int j=n;j>i;j--){
				if(i==0 || j==n || j==i+1){
					printf("%d",A[i][n-j]);
				}
				else printf(" ");
			}
			printf("\n");
		}
	}
}