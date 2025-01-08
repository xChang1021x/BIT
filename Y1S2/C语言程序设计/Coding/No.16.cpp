#include<stdio.h>

int main(){
	int n;
	while(~scanf("%d",&n)){
		int x=1;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				printf("%3d",x++);
			}
			printf("\n");
		}
	}
	return 0;
}