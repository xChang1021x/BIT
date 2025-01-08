#include<stdio.h>
#include<string.h>

int main(){
	char A[2][100]={0};
	char C[100]={0};
	int max,min,x=0;
	int a=0,b=0;
	gets(A[0]);
	gets(A[1]);
	while(x<=strlen(A[0])+strlen(A[1])){
		if(A[0][a]<=A[1][b] && A[0][a]!=0 &&A[0][b]!=0){
			C[x++]=A[0][a++];
		}
		else if(A[0][a]==0){
			C[x++]=A[1][b++];
		}
		else if(A[1][b]==0){
			C[x++]=A[0][a++];
		}
		else{
			C[x++]=A[1][b++];
		}

	}
	printf("%s\n",C);
}