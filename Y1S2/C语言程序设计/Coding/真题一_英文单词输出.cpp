#include<stdio.h>
#include<string.h>

int main(){
	int x=0,y=0,k=0;
	char A[1000]={0};
	char word[50][100]={0};
	char temp[100]={0};
	gets(A);
	while(x<strlen(A)){
		k=0;
		while(A[x]!=' ' && A[x]!=0){
			word[y][k++]=A[x++];
		}
		y++;
		x++;
	}
	for(int i=0;i<y-1;i++){
		for(int j=i+1;j<y;j++){
			if(strcmp(word[i],word[j])>0){
				strcpy(temp, word[i]);
				strcpy(word[i], word[j]);
				strcpy(word[j], temp);
			}
		}
	}
	for(int i=0;i<y;i++){
		printf("%s",word[i]);
		if(i!=y-1) printf(" ");
	}
	printf("\n");
}