#include<stdio.h>

int main(){
	int x;
	const int a=50,b=60,c=45;
	scanf("%d",&x);
	if(x%8!=0){
		printf("No change.\n");
	}
	else{
		x/=8;
		printf("%d,%d,%d\n",x*a,x*b,x*c);
	}
	return 0;
}