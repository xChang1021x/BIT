#include <stdio.h>
#include <string.h>

int main(){
	int n=1;
	while(n != 0){
		char tomTalk[100][10]={0};
		char temporaryStr[10]={0};
		int tomHonest=1;
		while(strcmp(tomTalk[n],"right on") != 0){
			scanf("%d",&n);
			getchar();
			if(n==0) break;  
			if(strcmp(tomTalk[n],"")==0){
				gets(tomTalk[n]);				
			}
			else{
				gets(temporaryStr);
				if(strcmp(temporaryStr, tomTalk[n])!=0){
					tomHonest=0;
					strcpy(tomTalk[n],temporaryStr);
				}
			}
		}
		if(n==0) break;
		if(tomHonest==1){
			for(int i=1;i<n;i++){
				if(strcmp(tomTalk[i],"too low")!=0 && strcmp(tomTalk[i],"")!=0){
					tomHonest=0;
				}
			}
			for(int i=n+1;i<=10;i++){
				if(strcmp(tomTalk[i],"too high")!=0 && strcmp(tomTalk[i],"")!=0){
					tomHonest=0;
				}
			}
		}
		if(tomHonest==1){
			printf("Tom may be honest\n");
		}
		else printf("Tom is dishonest\n");
	}
	return 0;
}