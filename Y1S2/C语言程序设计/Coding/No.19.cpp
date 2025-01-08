#include<stdio.h>

int main(){
	int day,month,year,year2,x,count;
	int months[15]={31,28,31,30,31,30,31,31,30,31,30,31};
	int month2=0,total=0,k=0;
	int mon[12]={0};
	while(~scanf("%d",&year,&month,&day)){
		x=0;
		count=0;
		month2=0;
		total=0;
		day=13;
		k=0;
		months[1]=28;
		if(year%4==0 && year%100!=0 || year%400==0){
			months[1]=29;
		}
		year2=year-1901;
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
		year2=k+year*365;
		for(month=1;month<13;month++){
			day=13;
			month2=0;
			for(int i=0;i<month-1;i++){
				month2+=months[i];
			}
			--day;
			total=day+month2+year2;
			total%=7;
			printf("(%d)",total);
			if(total==3){
				count+=1;
				mon[x++]=month;
				
			}
		}
		if(count>1) printf("There are %d Black Fridays in year %d.\n",count,year);
		else printf("There are %d Black Friday in year %d.\n",count,year);
		printf("They are:\n");
		for(int i=0;i<count;i++){
			printf("%d/%d/13\n",year,mon[i]);
		}
		
		
	}
	return 0;
}