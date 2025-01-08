#include<stdio.h>

int main(){
	int year,month,day,add;
	int months[15]={31,28,31,30,31,30,31,31,30,31,30,31};
	while(~scanf("%d %d %d %d",&year,&month,&day,&add)){
		day+=add;
		if(year%4==0 && year%100!=0 || year%400==0){
			months[1]=29;
		}
		while(day>months[month-1]){
			months[1]=28;
			if(year%4==0 && year%100!=0 || year%400==0){
				months[1]=29;
			}
			day-=months[month-1];
			month++;
			if(month>12){
				month-=12;
				year++;
			}
		}
		printf("%d.%d.%d\n",year,month,day);
	}
}