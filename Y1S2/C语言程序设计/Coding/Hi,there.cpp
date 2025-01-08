#include<stdio.h>

int main(){
	char A[100]={0};
	gets(A);
	printf("Hi,there,%s!\n",A);
	return 0;
}