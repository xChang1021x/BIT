#include<stdio.h>

int main(){
	int a,n,i=0,num=1,div=0;
	scanf("%d %d",&a,&n);
	for(i;i<n;i++){
		num*=a;
		div=num/1000;
		num%=1000;
		if(div!=0){
			break;
		}
	}
	for(i;i<n-1;i++){
		num*=a;
		num%=1000;
	}
	if(div==0) printf("The last 3 numbers is %d.\n",num);
	else printf("The last 3 numbers is %03d.\n",num);
	return 0;
}