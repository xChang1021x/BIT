#include<stdio.h>
#include<string.h>

int main(){
	char A[10][100]={0};
	char B[100]={0};
	int x,y,max;
	for(int i=0;i<5;i++){
		scanf("%s",A[i]);
	}
	for(int i=0;i<4;i++){
		for(int j=i+1;j<5;j++){
			if(sizeof(A[i])>sizeof(A[j])){
				x=sizeof(A[i]);
			}
			else x=sizeof(A[j]);
			if(strncmp(A[i],A[j],x)<0){
				strcpy(B,A[i]);
				strcpy(A[i],A[j]);
				strcpy(A[j],B);
			}
		}
	}
	for(int i=0;i<5;i++){
		printf("%s\n",A[i]);
	}
}