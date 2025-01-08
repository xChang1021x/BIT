#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(){
	char A[1000]={0};
	char temp;
	int flag=0,flag2=0;
	int x,k;
	gets(A);
	if( isalnum(A[strlen(A)-1])) flag=0;
	else flag=1;
	k = strlen(A) - flag ;
	if(k % 2 == 0) flag2=1;
	x = k / 2 - flag2;
	for(int i = 1 ; i <= k / 2 ; i++){
		if(A[x - i + flag2] > A[x+i]){
			temp = A[x - i + flag2];
			A[x - i + flag2] = A[x+i];
			A[x+i] = temp;
		}
	}
	
	printf("%s",A);
}
