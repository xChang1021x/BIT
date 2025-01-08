#include<stdio.h>

int main(){
	int a,b,c;
	scanf("%d %d",&a,&b);
	if(a<b){
		printf("min=%d\n",a);
	}
	else printf("min=%d\n",b);
	return 0;
}