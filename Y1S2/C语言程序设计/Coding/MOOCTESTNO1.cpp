#include<stdio.h>

int main(){
	int n;
	char x,y;
	while(~scanf("%d",&n)){
		getchar();
		scanf("%c",&x);
		for(int i=0;i<n;i++){
			y=x;
			for(int j=n-i;j>1;j--){
				printf(" ");
			}
			for(int j=0;j<2*i+1;j++){
				printf("%c",y);
				if(j<(2*i+1)/2){
					y++;
					if(y>'Z'){
						y-=26;
					}
				}
				else {
					y--;
					if(y<'A'){
						y+=26;
					}	
				}
			}
			printf("\n");
			x++;
			if(x>'Z'){
				x-=26;
			}
		}
	}
}