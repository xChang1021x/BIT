#include<stdio.h>
#include<string.h>

int main(){
	int n;
	while(~scanf("%d",&n)){
		char A[100]={0};
		int NUM[100]={0};
		int x=0,y=0,z=0;
		int panduan=0,panduan2=0,panduan3=0;
		for(int i=1;i<10;i++){
			if(i==n) continue;
			for(int j=1;j<10;j++){
				panduan2=0;
				memset(NUM,0,sizeof(A));
				if(j==i || j==n) continue;
				x=n*100+i*10+j;
				y=2*x;
				z=3*x;
				if(z>999){
					panduan=1;
					break;
				}
				A[0]=n;
				A[1]=i;
				A[2]=j;
				A[3]=y/100;
				A[4]=y/10%10;
				A[5]=y%10;
				A[6]=z/100;
				A[7]=z/10%10;
				A[8]=z%10;
				for(int l=0;l<9;l++) NUM[A[l]]+=1;
				for(int l=1;l<10;l++){
					if(NUM[l]!=1){
						panduan2=1;
						break;
					}
				}
				if(panduan2==0){
					printf("%d,%d,%d\n",x,y,z);
					panduan3=1;
				}
			}
			if(panduan==1){
				break;
			}
		}
		if(panduan3==0){
			printf("0,0,0\n");
		}
	}
}