#include<stdio.h>
#include<string.h>

int main(){
	int n;
	char A[1000]={0};
	while(~scanf("%d",&n)){
		for(int i=0;i<n;i++){
			getchar();
			int x=0;
			int y=0;
			int max,ling=0;
			int fuhaoweizhi;
			int panduan=0,panduan2=0;
			char fuhao;
			int B[1000]={0};
			int C[1000]={0};
			int sum[1000]={0};		
			scanf("%s",A);
			for(int j=0;j<strlen(A);j++){
				if(A[j]=='+' || A[j]=='-'){
					fuhaoweizhi=j;
					if(A[j]=='+'){
						fuhao='+';
					}
					else fuhao='-';
				}
			}
			for(int j=fuhaoweizhi-1;j>=0;j--){
				B[x++]=A[j]-'0';
			}
			for(int j=strlen(A)-1;j>fuhaoweizhi;j--){
				C[y++]=A[j]-'0';
			}
			if(x>y){
				max=x;
			}
			else max=y;
			if(fuhao=='+'){
				for(int j=0;j<max;j++){
					sum[j]=sum[j]+B[j]+C[j];
					while(sum[j]>=10){
						sum[j]-=10;
						sum[j+1]+=1;
					}
				}
			}
			else if(fuhao=='-'){
				for(int j=0;j<max;j++){
					sum[j]=sum[j]+B[j]-C[j];
					while(sum[j]<0){
						sum[j]+=10;
						sum[j+1]-=1;
					}
				}
				if(sum[max]<0){
					panduan2=1;
					sum[max]=-sum[max];
					for(int j=0;j<=max;j++){
						if(j==max) sum[j]=2-sum[j];
						else sum[j]=0-sum[j];
						while(sum[j]<0){
							sum[j]+=10;
							sum[j+1]+=1;
						}
					}
				}
			}
			for(int j=0;j<=max;j++){
				if(sum[j]==0){
					ling+=1;
				}
			}
			
			if(ling!=max+1){
				if(fuhao=='-' && panduan2==1){
					printf("-");
				}
				for(int j=max;j>=0;j--){
					if(sum[j]!=0 || panduan==1){
						printf("%d",sum[j]);
						panduan=1;
					}
				}
			}
			else printf("0");
			printf("\n");
		}
	}
}