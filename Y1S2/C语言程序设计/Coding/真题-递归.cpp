#include<stdio.h>

long findf(int n);

int main(){
	int n;
	scanf("%d",&n);
	printf("%ld\n",findf(n));
	return 0;
}

long findf(int n){
	if(n<=0) return 1;
	else if(n>0) return (n*findf(n-1) + findf(n-2));
	else return 1;
}