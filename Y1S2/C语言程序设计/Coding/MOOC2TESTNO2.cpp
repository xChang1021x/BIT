#include<stdio.h>

int main(){
	int n,x;
	char a;
	scanf("%d, %c",&n,&a);
	for(int i=0;i<n;i++){
		if(i!=n-1) x=i;
		else x=0;
		for(int j=0;j<n-x;j++){
			if(j==n-x-1 || i==0 || i==n-1){
				printf("%c",a);
				a++;
				if(a>'z') a-=26;
			}
			else printf(" ");
		}
		printf("\n");
	}
	return 0;
}