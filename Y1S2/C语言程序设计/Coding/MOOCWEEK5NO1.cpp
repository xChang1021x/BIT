#include<stdio.h>

int main(){
	int count;
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			for(int k=1;k<=j;k++){
				if(i*i==j*j+k*k){
					count++;
				}
			}
		}
	}
	printf("%d",count);
}