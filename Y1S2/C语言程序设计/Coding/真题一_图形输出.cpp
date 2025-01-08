#include<stdio.h>

int main(){
	int n,x;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		x=1;
		for(int j=0;j<i;j++){
			printf(" ");
		}
		for(int j=0;j<n-i;j++){
			printf("%d",x++);
		}
		printf("\n");
	}
}