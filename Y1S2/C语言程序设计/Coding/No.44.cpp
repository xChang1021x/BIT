#include<stdio.h>

int GCD(int n, int m);

int main(){
	int n,m;
	int gcd;
	scanf("%d %d",&n, &m);
	gcd=GCD(n,m);
	printf("%d\n",gcd);
	return 0;
}

int GCD(int n, int m){
	if(m<=n && n%m==0){
		return m;
	}
	else if(n<m){
		return GCD(m,n);
	}
	else return GCD(m, n%m);
}