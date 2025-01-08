#include<stdio.h>

int main(){
	long long int n1,n2;
	long long int sum1,sum2;
	while(~scanf("%lld %lld",&n1,&n2)){
		sum1=34;
		sum2=34;
		if(n1>4) sum1+=18*(n1-4)+(n1-5)*2*(n1-4);
		if(n2>4) sum2+=18*(n2-4)+(n2-5)*2*(n2-4);
		printf("%lld %lld\n",sum1,sum2);
	}
}