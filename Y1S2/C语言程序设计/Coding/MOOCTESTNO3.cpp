#include<stdio.h>
#include<string.h>

int main(){
	char A[2000]={0};
	char B[2000]={0};
	char C[2000]={0};
	char SAME[2000]={0};
	int x;
	gets(A);
	gets(B);
	gets(C);
	for(int i=0;i<strlen(A);i++){
		if(A[i]==B[0]){
			SAME[0]=A[i];
			for(int j=1;j<strlen(B);j++){
				SAME[j]=A[i+j];
			}
			if(strcmp(SAME,B)==0){
				if(C[0]==0){
					for(int k=i;k<strlen(A);k++){
						A[k]=A[k+strlen(B)];
					}
					i--;
					continue;
				}
				if(strlen(C)>strlen(B)){
					x=strlen(C)-strlen(B);
					for(int k=strlen(A)-1;k>=i+strlen(B);k--){
						A[k+x]=A[k];
					}
				}
				else if(strlen(B)>strlen(C)){
					x=strlen(B)-strlen(C);
					for(int k=i+strlen(B);k<=strlen(A);k++){
						A[k-x]=A[k];
					}
				}
				for(int k=i;k<i+strlen(C);k++){
					A[k]=C[k-i];
				}
				
			}
			if(strlen(A)>=1000){
				break;
			}
			i+=strlen(B)-1;
		}
	}
	printf("%1000s\n",A);
	return 0;
}