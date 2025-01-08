#include<stdio.h>

int main(){
	int n;
	while(~scanf("%d",&n)){
		int panduan=0;
		for(int i=n;i>1;i--){
			panduan=0;
			for(int j=2;j<i;j++){
				if(i%j==0){
					panduan=1;
					break;
				}
			}
			if(panduan==0){
				printf("The max prime number is %d.\n",i);
				break;
			}
		}
		
	}
}