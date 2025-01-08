#include<stdio.h>
#include<string.h>

int main(){
	int n;
	while(~scanf("%d",&n)){
		int A[1000]={0};
		int B[1000]={0};
		int C[1000]={0};
		int x=0,sum=0;
		for(int i=0;i<2*n;i++){
			A[i]=i+1;
		}
		for(int i=0;i<2*n;i++){
			B[i]=A[i];
		}
		while(++x){
			sum=0;
			for(int i=0;i<n;i++){
				C[2*i+1]=A[i];
			}
			for(int i=0;i<n;i++){
				C[2*i]=A[i+n];
			}
			for(int i=0;i<2*n;i++){
				A[i]=C[i];
			}
			for(int i=0;i<2*n;i++){
				if(C[i]==B[i]){
					sum+=1;
				}
			}
			if(sum==2*n){
				break;
			}
		}
		printf("%d\n",x);
	}
}