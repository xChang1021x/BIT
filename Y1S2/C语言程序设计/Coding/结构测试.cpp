#include<stdio.h>
#include<string.h>

struct dictionary{
	char word[100];
} link[1000];

void fenli(char *str, int *num);

int main(){
	char A[1000]={0};
	int k=0;
	while(fgets(A,1000,stdin) != NULL){
		fenli(A,&k);
		printf("\n");
	}
}

void fenli(char *str,int *num){
	char B[1000]={0};
	char *p=str;
	int x=0,k=*num;
	while((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z')){
		B[x++]=*p++;
	}
	for(int i=0;i<k;i++){
		if(strcmp(B,link[i].word)==0){
			printf("%d",i+1);
			break;
		}
		else if(i==k-1){
			strcpy(link[(*num)++].word,B);
			printf("%s",B);
		}
	}
	if(*num==0){
		strcpy(link[0].word,B);
		printf("%s",B);
		(*num)++;
	}
	while(*p != '\n' && (*p < 'a' || *p >'z') && (*p <'Z' || *p >'A')){
		if(*p == ' '){
			printf(" ");
			break;
		}
		else printf("%c",*p++);
	}
	if(*p != ' ' && *p != '\n') fenli(p,num);
	else if(*p == ' ') fenli(p+1,num);
	else return;
}

