#include<stdio.h>
#include<math.h>

int main(){
	int m,n;
	int sum=0;
	scanf("%d,%d",&m,&n);
	for(int i=m;i<=n;i++){
		if((int)sqrt(i)*(int)sqrt(i)==i){
			sum+=i;
		}
	}
	printf("%d",sum);
	return 0;
}