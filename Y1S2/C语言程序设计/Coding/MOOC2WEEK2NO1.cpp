#include<stdio.h>

int HCF(int m,int n){
	if(m % n ==0)
		return n;
	else 
		return HCF(n,m%n);
}

int main(){
	int m,n;
	scanf("%d,%d",&m,&n);
	printf("%d\n",HCF(m,n));
	return 0;
}