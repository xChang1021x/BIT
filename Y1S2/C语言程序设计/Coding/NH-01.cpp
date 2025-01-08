#include<stdio.h>
#include<math.h>
//first will be 2(K=1) or 3(K=2)
//second is abs(720/a)%10
//third must be 1
//fourth is the ten place of (LCM of 463 and b)

int main(){
	int K,a,b,x,HCF;
	scanf("%d %d %d",&K,&a,&b);
	for(int i=463;i>0;i--){
		if(b%i==0 && 463%i==0){
			HCF=i;
			break;
		}
	}
	printf("%d%d%d%d\n",K+1,abs(720/a)%10,1,(463*b/HCF)/10%10);
	return 0;
}