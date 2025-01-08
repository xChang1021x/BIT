#include<stdio.h>
#include<string.h>

int main(){
	char A[100]={0};
	char his[100]={0};
	int panduan=0,x=0;
	scanf("%s",A);
	for(int i=0;i<strlen(A);i++){
		panduan=0;
		for(int j=0;j<strlen(his);j++){
			if(A[i]==his[j]){
				panduan=1;
				break;
			}
		}
		if(panduan==1) continue;
		his[x++]=A[i];
		printf("%c",A[i]);
	}
	printf("\n");
}