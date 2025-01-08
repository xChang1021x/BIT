#include<stdio.h>

int duck(int n, int sum){
	if(n!=1){
		return duck(n-1,sum*2+2);	
	}
	else return sum*2+2;
}

void sell(int n, int sum){
	if(n!=7){
		printf("sell=%d,",sum/2+1);
		sell(n+1,sum/2-1);
	}
	else printf("sell=%d,\n",sum/2+1);
}

int main(){
	int n=7,sum=2;
	sum=duck(n,sum);
	printf("sum=%d\n",sum);
	sell(1,sum);
	return 0;
}