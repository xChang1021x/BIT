#include<stdio.h>
#include<string.h>

int main(){
	char word[50]={'a','b','c','d','e','i','k',';','w',
			    	'd','w','k',';','i','a','b','c','e'};
	char A[100]={0};
	int flag;			
	gets(A);
	for(int i=0;i<strlen(A);i++){
		flag=0;
		for(int j=0;j<9;j++){
			if(A[i]==word[j]){
				printf("%c",word[j+9]);
				flag=1;
				break;
			}
		}
		if(flag==0) printf("%c",A[i]);
	}
	printf("\n");
	
}