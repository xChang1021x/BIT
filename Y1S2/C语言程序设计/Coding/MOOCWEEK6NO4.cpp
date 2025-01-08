#include<stdio.h>

int main(){
	int t,n;
	scanf("%d",&t);
	for(int i=0;i<t;i++){
		int x;
		int max=-1001, sum=0, sum2=0;
		scanf("%d",&n);
		for(int j=0;j<n;j++){
			scanf("%d",&x);
			if(max<x) max=x;
			if(sum+x>0) sum+=x;
			else sum=0;
			if(sum2<sum) sum2=sum;
		}
		if(max<0) printf("%d\n",max);
		else printf("%d\n",sum2);
	}
	return 0;
}