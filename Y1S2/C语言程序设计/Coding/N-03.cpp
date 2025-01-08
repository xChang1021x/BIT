#include<stdio.h>
#include<math.h>

int main(){
	int m,n,a,b,x;
	scanf("%d %d %d %d",&m,&n,&a,&b);
	x=abs(m-b*n)/abs(a-b);
	printf("%d %d\n",x,n-x);
	return 0;
}