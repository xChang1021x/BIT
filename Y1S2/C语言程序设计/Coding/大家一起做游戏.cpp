#include<stdio.h>

int main(){
	int n,m;
	while(~scanf("%d %d",&n, &m)){
		int A[100]={0};
		int count=0,x=0,k=0;
		while(k!=n-1){
			x++;
			count++;
			if(x>n) x-=n;
			while(A[x]!=0){
				x++;
				if(x>n) x-=n;
			}
			if(count==m){
				A[x]+=1;
				k++;
				count=0;
			}
		}
		for(int i=1;i<=n;i++){
			if(A[i]==0){
				printf("The left child is NO %d.\n",i);
			}
		}
	}
}