#include<stdio.h>

int main(){
	int A[5]={0};
	while(~scanf("%d %d %d %d",&A[0],&A[1],&A[2],&A[3])){
		int sum=0,x=0;
		A:x++;
		for(int i=0;i<4;i++){
			sum=A[i];
			if(sum==x){
				goto A;	
			}
			for(int j=0;j<=i;j++){
				sum=A[i]+A[j];
				if(sum==x){
					goto A;	
				}
				for(int k=0;k<=j;k++){
					sum=A[i]+A[j]+A[k];
					if(sum==x){
						goto A;	
					}
					for(int l=0;l<=k;l++){
						sum=A[i]+A[j]+A[k]+A[l];
						if(sum==x){
							goto A;	
						}
						for(int m=0;m<=l;m++){
							sum=A[i]+A[j]+A[k]+A[l]+A[m];
							if(sum==x){
								goto A;
							}
						}
					}
				}
			}
		}
		printf("The max is %d.\n",x-1);
	}
}