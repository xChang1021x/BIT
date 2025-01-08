#include<stdio.h>
#include<string.h>

int main(){
	char A[100]={0};
	char temp;
	while(~scanf("%s",A)){
		for(int i=0;i<strlen(A)-1;i++){
			for(int j=i;j<strlen(A);j++){
				if(A[i]<A[j]){
					temp=A[i];
					A[i]=A[j];
					A[j]=temp;
				}
			}
		}
		printf("%s\n",A);
	}
}