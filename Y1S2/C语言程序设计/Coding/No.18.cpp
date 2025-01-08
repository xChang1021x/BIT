#include<stdio.h>
#include<math.h>

int main(){
	int n,sum,x,y,jihao;
	while(~scanf("%d",&n)){
		jihao=0;
		for(int i=(int)pow(10,n-1);i<(int)pow(10,n);i++){
			sum=0;
			for(int j=0;j<n;j++){
				y=1;
				x=(i/(int)pow(10,j))%10;
				for(int k=0;k<n;k++){
					y*=x;
				}
				sum+=y;
			}
			if(sum==i){
				printf("%d\n",i);
				jihao=1;
			}
		}
		if(jihao==0){
			printf("No output.\n");
		}

	}
}