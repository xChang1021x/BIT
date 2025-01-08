#include<stdio.h>

int sum(int n){
	if(n!=1)
		return n + sum(n-2);
	else
		return 1;
}

int main(){
	int n;
	scanf("%d",&n);
	printf("%d\n",sum(2*n-1));
}