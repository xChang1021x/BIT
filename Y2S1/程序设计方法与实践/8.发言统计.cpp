#include<stdio.h>
#include<string.h>

int main(){
	int n,sum=0,flag;
	char talkHistory[1010][30]={0};
	scanf("%d",&n);
	getchar();
	for(int i=0;i<n;i++){
		flag=1;
		gets(talkHistory[i]);
		if(strlen(talkHistory[i])<=10) continue;
		for(int j=0;j<i;j++){
			if(strcmp(talkHistory[i],talkHistory[j])==0){
				flag=0;
			}
		}
		if(flag){
			sum+=1;
		}
	}
	printf("%d\n",sum);
}