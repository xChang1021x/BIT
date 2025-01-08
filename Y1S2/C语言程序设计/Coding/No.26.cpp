#include<stdio.h>

int main(){
	int n;
	while(~scanf("%d",&n)){
		int k=n+1;
		for(int i=0;i<n;i++){
			k=n;
			for(int j=n-1;j>i;j--){
				printf("  ");
			}
			for(int j=0;j<2*i+1;j++){
				if(j>=i){
					printf("%d",k++);
					if(k-1<10){
						printf(" ");
					}
				}
				else{
					printf("%d",k--);
					if(k+1<10){
						printf(" ");
					}
				}
			}
			printf("\n");
		}
		for(int i=n-1;i>0;i--){
			k=n;
			for(int j=n-1;j>=i;j--){
				printf("  ");
			}
			for(int j=2*i-2;j>=0;j--){
				if(j<i){
					printf("%d",k++);
					if(k-1<10){
						printf(" ");
					}
				}
				else{
					printf("%d",k--);
					if(k+1<10){
						printf(" ");
					}
				}
			}
			printf("\n");
		}
	}
}