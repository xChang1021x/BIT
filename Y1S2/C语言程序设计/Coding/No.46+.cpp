#include<stdio.h>
#include<string.h>

int main(){
	char A[10]={0};
	int count=0;
	int panduan=0;
	while(~scanf("%s",A)){
		count=0;
		panduan=0;
		if(A[4]<'0' || A[4]>'9'){
			printf("no.\n");
			continue;
		}
		if(strlen(A)!=5){
			printf("no.\n");
		}
		for(int i=0;i<strlen(A);i++){
			if(A[i]=='I' || A[i]=='O'){
				printf("no.\n");
				panduan=1;
				break;
			}
			else if(A[i]>='A' && A[i]<='Z'){
				count++;
			}
		}
		if(panduan){
			continue;
		}
		if(count==2){
			printf("ok.\n");
		}
		else printf("no.\n");
	}
}