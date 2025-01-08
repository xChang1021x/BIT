#include<stdio.h>  
#include<string.h>  
  
int main(){  
    char A[100]={0};  
    char B[100]={0};  
    gets(A);
	gets(B);  
    int panduan=0;  
    for(unsigned int i=0;i<strlen(A);i++){  
        panduan=0;  
        for(unsigned int j=0;j<strlen(B);j++){  
        if(A[i]==B[j]){  
                panduan=1;  
                break;  
            }  
        }  
        if(panduan==0) printf("%c",A[i]);  
    }  
    printf("\n"); 
} 