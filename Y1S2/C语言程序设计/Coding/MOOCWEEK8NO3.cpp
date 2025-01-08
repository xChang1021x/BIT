#include<stdio.h>
#include<string.h>

int main(){
	int n;
	int W[20]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
	char A[50]={0};
	char B[50]={0};
	while(~scanf("%d",&n)){
		getchar();
		for(int i=0;i<n;i++){
			int sum=0;
			gets(A);
			strcpy(B,A);
			if(strlen(A)!=15 && strlen(A)!=18){
				printf("Invalid\n");
				continue;
			}
			if(strlen(A)==15){
				for(int i=14;i>=6;i--){
					A[i+2]=A[i];
				}
				A[6]='1';
				if(A[14]=='9'&&A[15]=='9'&&(A[16]=='6'||A[16]=='7'||A[16]=='8'||A[16]=='9')){
					A[7]='8';
				}
				else A[7]='9';
			}
			else if(A[6]!='1' && A[6]!='2'){
				printf("Invalid\n");
				continue;
			}
			else if(A[6]=='1' && A[7]<'8'){
				printf("Invalid\n");
				continue;
			}
			else if(A[6]=='2' && A[7]>'0'){
				printf("Invalid\n");
				continue;
			}
			for(int i=0;i<17;i++){
				sum+=(A[i]-'0')*W[i];
			}
			sum%=11;
			switch(sum){
				case 0:
					A[17]='1';
					break;
				case 1:
					A[17]='0';
					break;
				case 2:
					A[17]='X';
					break;
				case 3:
					A[17]='9';
					break;
				case 4:
					A[17]='8';
					break;
				case 5:
					A[17]='7';
					break;
				case 6:
					A[17]='6';
					break;
				case 7:
					A[17]='5';
					break;
				case 8:
					A[17]='4';
					break;
				case 9:
					A[17]='3';
					break;
				case 10:
					A[17]='2';
					break;
			}
			if(strlen(B)==18){
				if(strcmp(A,B)==0){
					printf("Valid\n");
				}
				else printf("Invalid\n");
			}
			else{
				printf("%s\n",A);
			}
		}
	}
}