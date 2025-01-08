#include<stdio.h>

int main(){
	int n;
	while(~scanf("%d",&n)){
		for(int i=n;i>0;i--){
			for(int j=n;j>i;j--){
				printf(" ");
			}
			for(int j=0;j<2*i-1;j++){
				if(i==n || j==0 || j==2*i-2) printf("*");
				else printf(" ");
			}
			printf("\n");
		}
	}
}