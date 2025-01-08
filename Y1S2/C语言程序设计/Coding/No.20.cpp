#include<stdio.h>  
  
int main(){  
    int a,b;  
    char o;  
    int result;  
    while(~scanf("%d%c%d",&a,&o,&b)){  
        switch(o){  
            case '+':  
                result=a+b;  
                break;  
            case '-':  
                result=a-b;  
                break;  
            case '*':  
                result=a*b;  
                break;  
            case '/':  
                result=a/b;  
                break;  
            case '%':  
                result=a%b;  
                break;    
        }  
        printf("%d\n",result);  
    }  
}