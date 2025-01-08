#include<stdio.h>
#include<string.h>

int main(){
	int n,j=0,k=0;
	char x,y;
	char A[100][100];
	memset(A,' ',sizeof(A));
	scanf("%d %c",&n,&x);
	y=x;
	if(n==1){
		printf("%c\n",x);
		return 0;
	}	
	for(int i=0;i<3*n-3;i++){
		if(i<n-1){
			A[j++][k++]=x++;
			if(x>'Z') x-=26;
		}
		else if(i<2*(n-1)){
			A[j][k--]=x++;
			if(x>'Z') x-=26;
		}
		else{
			A[j--][k]=x++;
			if(x>'Z') x-=26;
		}
	}
	x=y;
	j=0;
	k=2*n-2;
	for(int i=0;i<3*n-3;i++){
		if(i<n-1){
			A[j++][k--]=x++;
			if(x>'Z') x-=26;
		}
		else if(i<2*(n-1)){
			A[j][k++]=x++;
			if(x>'Z') x-=26;
		}
		else{
			A[j--][k]=x++;
			if(x>'Z') x-=26;
		}
		
	}
	for(int i=0;i<n;i++){
		for(int l=0;l<n*2-1;l++){
			printf("%c",A[i][l]);
			if(l!=n*2-2) printf(" ");
		}
		printf("\n");
	}
	return 0;
}