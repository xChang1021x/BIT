#include <stdio.h>
#include <math.h>

int main(){
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;i++){
		long long int alcoAmount,ratAmount=0;		
		scanf("%lld",&alcoAmount);
		for(int j=0;j<alcoAmount;j++){
			if(pow(2,j)>=alcoAmount){
				ratAmount = j;
				break;
			}
		}
		printf("%d\n",ratAmount);
	}
}