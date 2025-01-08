#include<stdio.h>  
  
int main(){  
    int a,b;  
    int ge,shi,bai,qian;  
    int counter;  
    while(~scanf("%d %d",&a,&b)){  
        counter=0;  
        if(a==0 && b==0){  
            return 0;  
        }  
        if(a>b){  
            printf("Error\n");  
            continue;  
        }  
        if(a<1000 || a>=10000 || b>=10000){  
            printf("Error\n");  
            continue;  
        }  
        for(int i=a;i<=b;i++){  
            if(i%2!=0){  
                continue;  
            }  
            ge=i%10;  
            shi=i/10%10;  
            bai=i/100%10;  
            qian=i/1000;  
            if(ge!=shi && ge!=bai && ge!=qian && shi!=bai && shi!=qian && bai!=qian){  
                printf("%d  ",i);  
                counter++;  
            }  
        }  
        printf("\n");  
        printf("counter=%d\n",counter);  
    }  
} 