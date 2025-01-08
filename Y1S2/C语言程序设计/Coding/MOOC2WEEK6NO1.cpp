#include<stdio.h>
#include<string.h>

int main(){
	char A[100]={0};
	char B[100]={0};
	int x,count=0;
	gets(A);
	gets(B);
	while(x<strlen(A)){
		if(A[x]==B[0]){
			for(int i=1;i<strlen(B);i++){
				if(A[x+i]!=B[i]) break;
				else if(i==strlen(B)-1){
					count++;
					x+=strlen(B);
				}
			}
		}
		else x++;
	}
	if(count!=0) printf("%d\n",count);
	else printf("No\n");
	return 0;
}