#include<stdio.h>

int main(){
	int n;
	char s;
	while(~scanf("%c %d",&s,&n)){
		getchar();
		for(int i=0;i<n;i++){
			for(int j=n-i-1;j>0;j--){
				printf(" ");
			}
			for(int j=0;j<2*i+1;j++){
				if(j==0 || j==2*i) printf("%c",s);
				else printf(" ");
			}
			printf("\n");
			s++;
			if(s>'Z'){
				s-=26;
			}
		}
		s-=2;
		for(int i=0;i<n-1;i++){
			for(int j=0;j<=i;j++){
				printf(" ");
			}
			for(int j=0;j<2*n-3-2*i;j++){
				if(j==0 || j==2*n-4-2*i) printf("%c",s);
				else printf(" ");
			}
			printf("\n");
			s--;
			if(s<'A'){
				s+=26;
			}
		}
	}
}