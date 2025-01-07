#include<stdio.h>

int main(){
	int n,h,x=1,flag=0;
	long long int totalDay=0;
	int targetMap[100000]={0};
	scanf("%d %d",&n,&h);
	for(int i=1;i<=n;i++){
		scanf("%d",&targetMap[i]);
	}
	targetMap[n+1]=h;
	for(int i=1;i<=n;i++){
		if(targetMap[i+1]>targetMap[i]){
			totalDay+=targetMap[i+1]-targetMap[i];
		}
	}
	printf("%lld\n",totalDay);
}