#include<stdio.h>

int main(){
	int n;
	int A[100]={0};
	while(~scanf("%d",&n)){
		for(int i=0;i<n;i++){
			scanf("%d",&A[i]);
		}
		for(int i=0;i<(n-1)/2+1;i++){
			if(i!=n-i-1){
				printf("%d ",A[i]*A[n-i-1]);
			}
			else printf("%d ",A[i]);
		}
		printf("\n");
	}
}