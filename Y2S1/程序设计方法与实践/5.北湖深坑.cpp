#include <stdio.h>

int main(){
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;i++){
		int n,x=1,y=0,highest=0,highest2=0,flag=0,flag2=0;
		long long int targetMap[100000]={0};
		long long int totalWater=0;
		scanf("%d",&n);
		for(int j=1;j<=n;j++){
			scanf("%lld",&targetMap[j]);
		}
		
		for(int j=1;j<=n;j++){
			if(targetMap[j]!=0 && flag==0){
				highest=targetMap[j];
				x=j;
				j++;
				flag=1;
			}
			else if(flag==0){
				continue;
			}
			
			if(targetMap[j]>=highest){
				for(int k=1;k<j-x;k++){
					totalWater += targetMap[x]-targetMap[x+k];
				}
				highest=targetMap[j];
				x=j;
			}
		}
	
		for(int j=n;j>=1;j--){
			if(targetMap[j]!=0 && flag2==0){
				highest2=targetMap[j];
				y=j;
				j--;
				flag2=1;
			}
			else if(flag2==0){
				continue;
			}
			
			if(targetMap[j]>=highest2){
				for(int k=1;k<y-j;k++){
					totalWater += targetMap[y]-targetMap[y-k];
				}
				highest2=targetMap[j];
				y=j;
			}
		}
		
		for(int j=1;j<x-y;j++){
			totalWater -= targetMap[y] - targetMap[y+j];
		}
		
		printf("%lld\n",totalWater);
	}

}