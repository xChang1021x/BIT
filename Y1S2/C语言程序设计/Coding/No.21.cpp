#include<stdio.h>    
    
int main(){    
    int day,month,year;    
    int months[15]={31,28,31,30,31,30,31,31,30,31,30,31};    
    int month2=0,total=0,k=0,result;    
    while(~scanf("%d",&year)){    
        month2=0;  
        total=0;  
        k=0;  
        months[1]=28;   
        month=5;  
        day=1;  
        if(year%4==0 && year%100!=0 || year%400==0){     
            months[1]=29;  
        }  
        year=year-1601;    
        for(int i=1;i<=year;i++){    
            if(i%4==0){    
                if(i%100==0){    
                    if(i%400==0){    
                        k++;    
                    }    
                }    
                else k++;    
            }    
        }    
        year=k+year*365;        
        for(int i=0;i<month-1;i++){    
            month2+=months[i];    
        }    
        --day;    
        total=day+month2+year;    
        total%=7;  
        if(total==0) total=7;  
        result=14-total;  
        printf("%d\n",result);  
    }  
    return 0;    
} 