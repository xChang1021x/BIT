#include<stdio.h>

int main(){
	int x;
	while(~scanf("%d",&x)){
		int k=25;
		switch(x){
			case 1:
				printf("3\n");
				k-=3;
				break;
			case 2:
				printf("2\n");
				k-=2;
				break;
			case 3:
				printf("1\n");
				k-=1;
				break;
		}
		k-=x;
		while(k>0){
			scanf("%d",&x);
			k-=x;
			if(k==0) break;
			switch(x){
			case 1:
				printf("3\n");
				k-=3;
				break;
			case 2:
				printf("2\n");
				k-=2;
				break;
			case 3:
				printf("1\n");
				k-=1;
				break;
			}
			
		}
		printf("Game Over!\n");
	}
}