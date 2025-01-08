#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]){
	char A[300],B[50],C[50],T[300],*pt;
	int lb;
	scanf("%s%s%s",A,B,C);
	lb=strlen(B);
	while(pt=strstr(A,B)){
		strcpy(T,pt+lb);
		strcpy(pt,C);
		strcat(A,T);
	}
	puts(A);
	return 0;
}