#include<stdio.h>

int main(){
	int n;
	int sum;
	while(~scanf("%d",&n)){
		sum=1;
		for(int i=n-1;i>0;i--){
			sum+=i;
			sum*=2;
		}
		if(sum!=1) printf("The monkey got %d peaches in first day.\n",sum);
		else printf("The monkey got 1 peach in first day.\n");
	}
}