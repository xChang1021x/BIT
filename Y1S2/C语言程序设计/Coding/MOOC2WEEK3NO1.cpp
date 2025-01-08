#include<stdio.h>

int fun1(int n, int x){
	if(n==1){
		return x;
	}
	else if(n%2==0){
		if(n/2==1) printf("%d\n",n/2);
		else printf("%d,",n/2);
		return fun1(n/2,x+1);
	}
	else{
		printf("%d,",n*3+1);
		return fun1(n*3+1,x+1);	
	}
}

int main(){
	int n,x=1;
	scanf("%d",&n);
	printf("%d,",n);
	x=fun1(n,x);
	printf("step=%d\n",x);
	return 0;
}