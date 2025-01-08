#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main(){
	char A[1000]={0};
	int n;
	while(~scanf("%d",&n)){
		int a=0,b=0,c=0,d=0;
		getchar();
		for(int i=0;i<n;i++){
			a=0,b=0,c=0,d=0;
			gets(A);
			if(strlen(A)<6){
				printf("Not Safe\n");
				continue;
			}
			for(int j=0;j<strlen(A);j++){
				if(islower(A[j])){
					a+=1;
				}
				else if(isupper(A[j])){
					b+=1;
				}
				else if(isdigit(A[j])){
					c+=1;
				}
				else d+=1;
			}
			if((a!=0) + (b!=0) + (c!=0) + (d!=0) > 2){
				printf("Safe\n");
			}
			else if((a!=0) + (b!=0) + (c!=0) + (d!=0) == 2){
				printf("Medium Safe\n");
			}
			else printf("Not Safe\n");
		}
	}
}