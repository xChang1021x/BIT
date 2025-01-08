#include<stdio.h>

int main(){
	int n;
	while(~scanf("%d",&n)){
		int A[100][100]={0};
		int k=1;
		int loop=0;
		int x=0,y=0;
		A[0][0]=k++;
		while(k<n*n+1){
			while(y<n-1+loop && A[x][y+1]==0){
				A[x][++y]=k++;
			}
			while(x<n-1+loop && A[x+1][y]==0){
				A[++x][y]=k++;
			}
			while(y>0+loop && A[x][y-1]==0){
				A[x][--y]=k++;
			}
			while(x>0+loop && A[x-1][y]==0){
				A[--x][y]=k++;
			}
			loop++;
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				printf("%3d",A[i][j]);
			}
			printf("\n");
		}
	}
}