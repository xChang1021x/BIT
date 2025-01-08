#include<stdio.h>  
  
int main(){  
    char a;  
    int n;  
    while(~scanf("%c,%d",&a,&n)){  
        getchar();  
        for(int i=0;i<n;i++){  
            for(int j=0;j<n+i;j++){  
                if(j==n-i-1 || j==n+i-1) printf("%c",a);  
                else printf(" ");  
            }  
            printf("\n");  
            a++;  
            if(a>'Z') a-=26;  
        }  
        a-=2;  
        for(int i=n-2;i>=0;i--){  
            for(int j=0;j<n+i;j++){  
                if(j==n+i-1 || j==n-i-1) printf("%c",a);  
                else printf(" ");  
            }  
        printf("\n");  
        a--;  
        if(a<'A') a+=26;  
        }  
    }  
}  