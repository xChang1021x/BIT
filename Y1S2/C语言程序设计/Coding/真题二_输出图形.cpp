#include<stdio.h>
#include<ctype.h>

int main(){
	int n;
	char x,y;
	while(~scanf("%d %c",&n,&x)){
		x=toupper(x);
		if(n % 2 != 1 || x<'A' || x>'Z'){
			printf("input error!\n");
			continue;
		}
		else{
			for(int i=0;i<n;i++){
				y=x;
				for(int j=0;j<n;j++){
					if(i==0 || i==n-1 || j==0 || j==n-1 || j==n/2){
						printf("%c",y);
						y++;
						if(y>'Z') y-=26;
					}
					else{
						printf(" ");
						y++;
						if(y>'Z') y-=26;
						
					}
				}
				printf("\n");
				x++;
				if(x>'Z') x-=26;
			}
		}
	}
	return 0;
}