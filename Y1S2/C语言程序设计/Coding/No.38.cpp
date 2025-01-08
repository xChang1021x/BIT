#include<stdio.h>  
  
int sum(int n , int m){  
    if(m==n){  
        return n;  
    }  
    else return sum(n,m-1)+m;  
}  
  
int main(){  
    int n,m;  
    int total;  
    scanf("%d %d",&n,&m);  
    total=sum(n,m);  
    printf("The sum from %d to %d is %d.\n",n,m,total);  
    return 0;  
}  