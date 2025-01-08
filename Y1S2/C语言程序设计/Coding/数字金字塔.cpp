#include<stdio.h>

int main(){
	int n;
	while(~scanf("%d",&n)){
		int k=1;
		for(int i=0;i<n;i++){
			k=1;
			for(int j=2*n-2-2*i;j>=0;j--){
				printf(" ");
			}
			for(int j=0;j<2*i+1;j++){
				if(j<i) printf("%d",k++);
				else printf("%d",k--);
				if(j!=2*i) printf(" ");
			}
			printf("\n");
		}
	}
}