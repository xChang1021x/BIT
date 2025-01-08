#include <stdio.h>    
#include <stdlib.h>  
#include <string.h>   
  
void reverse(char str[], int start ,int end);    
int main( )    
{   char str[100]={0};    
    int start, end;    
    gets(str);    
    scanf("%d%d", &start, &end);    
    reverse( str, start, end );    
    printf("%s\n", str);    
    return 0;    
}  
  
void reverse(char str[], int start ,int end){  
    char t;  
    if(start!=end && start<end){  
        if(start<strlen(str)-1){  
            if(end>strlen(str)) end=strlen(str)-1;  
            t=str[start];  
            str[start]=str[end];  
            str[end]=t;  
            reverse( str, start+1, end-1);            
        }  
  
    }  
} 