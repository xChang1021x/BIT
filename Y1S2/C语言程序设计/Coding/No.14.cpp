#include<stdio.h>

int main(){
	int day,month,year;
	int months[15]={31,28,31,30,31,30,31,31,30,31,30,31};
	int month2=0,total=0,k=0;
	while(~scanf("%d %d %d",&year,&month,&day)){
		month2=0;
		total=0;
		k=0;
		months[1]=28;
		if(year%4==0 && year%100!=0 || year%400==0){
					months[1]=29;
		}
		year=year-1901;
		for(int i=1;i<=year;i++){
			if((i+300)%4==0){
				if((i+300)%100==0){
					if((i+300)%400==0){
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
		if(total==0){
			printf("2\n");
		}
		else if(total==1){
			printf("3\n");
		}
		else if(total==2){
			printf("4\n");
		}
		else if(total==3){
			printf("5\n");
		}
		else if(total==4){
			printf("6\n");
		}
		else if(total==5){
			printf("0\n");
		}
		else if(total==6){
			printf("1\n");
		}
	}
	return 0;
}