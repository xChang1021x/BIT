#include<stdio.h>
#include<string.h>

int main(){
	int n;
	while(~scanf("%d",&n)){
		int fang,x=0,y=0;
		char A[100]={0};
		char B[100]={0};
		for(int i=1;i<n;i++){
			memset(A,0,sizeof(A));
			memset(B,0,sizeof(B));
			x=0;
			fang=i*i;
			while(fang>=10){
				A[x++]=fang%10 + '0';
				fang/=10;
			}
			A[x++]='0'+fang;
			for(int j=x-1;j>=0;j--){
				B[x-1-j]=A[j];
			}
			if(strcmp(A,B)==0){
				printf("%d\n",i);
			}
		}
	}
}