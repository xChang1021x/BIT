#include<stdio.h>  
   
double sum(int n);  
  
int main(){  
    int n;  
    double total;  
    while(~scanf("%d",&n)){  
        total=sum(n);  
        printf("sum=%.6lf\n",total);  
    }  
}  
  
double sum(int n){  
    if(n==1){  
        return 1;  
    }  
    else return sum(n-1) + 1.0/n;  
}  