#include<stdio.h>

int main(){
	int n,m;
	while(~scanf("%d %d",&n,&m)){
		int jihao=0;
		for(int i=n;i<=m;i++){
			if(i%3==0){
				printf("%d\n",i);
				jihao=1;
			}
		}
		if(jihao==0) printf("\n");
	}
}