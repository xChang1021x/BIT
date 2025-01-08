#include<stdio.h>

int main(){
	int n;
	while(~scanf("%d",&n)){
		int sum=0;
		if(n==0){
			printf("0\n");
			continue;
		}
		for(int i=1;i<=n;i++){
			sum+=i;
			if(sum>=n){
				printf("%d\n",i);
				break;
			}
		}
		
	}
}