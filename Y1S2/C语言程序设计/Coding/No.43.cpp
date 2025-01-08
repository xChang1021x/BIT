#include<stdio.h>  
   
double sum(int n);  
  
int main(){  
    int n;  
    double total;  
    while(~scanf("%d",&n)){  
        total=sum(n);  
        if(total!=1) printf("%.6lf\n",total);  
        else printf("1\n");  
    }  
}  
  
double sum(int n){  
    if(n==1){  
        return 1;  
    }  
    else if(n%2==0) return sum(n-1) + 1.0/n;  
    else return sum(n-1) - 1.0/n;  
}  