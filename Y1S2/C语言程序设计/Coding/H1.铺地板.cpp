#include<stdio.h>

int main(){
	int n;
	int A[100][100]={0};
	while(~scanf("%d",&n)){
		int k=2;
		int x=0,y=0;
		A[0][0]=1;
		for(int i=1;i<n;i++){
			if(i>n/2 && i!=n/2) A[++x][y]=k++;
			else A[x][++y]=k++;
			
			while(x+1<n && y>0){
				A[++x][--y]=k++;
			}
			
			if(n%2==0){
				if(i>=n/2) A[x][++y]=k++;
				else A[++x][y]=k++;
			}
			else{
				if(i>n/2) A[x][++y]=k++;
				else A[++x][y]=k++;
			}
			while(x>0 && y+1<n){
				A[--x][++y]=k++;
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				printf("%2d",A[i][j]);
				if(j!=n-1) printf(" ");
			}
			printf("\n");
		}
	}
}