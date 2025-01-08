#include<stdio.h>
#include<string.h>

int main(){
	int n;
	while(~scanf("%d",&n)){
		int A[1000]={0};
		memset(A,0,sizeof(A));
		int x=3;
		int k;
		A[1]+=1;
		A[3]+=1;
		for(int i=2;i<=n*2;i++){
			x+=i+1;
			while(x>n){
				x-=n;
			}
			A[x]+=1;
		}
		for(int i=1;i<=n;i++){
			if(A[i]==0){
				k=i;
			}
		}
		for(int i=1;i<=n;i++){
			if(i!=k && A[i]==0) printf("%d ",i);
			else if(i==k && A[i]==0) printf("%d",i);
		}
		printf("\n");
	}
}