#include<stdio.h>

int main(){
	int n;
	int year,month,day;
	int months[15]={31,28,31,30,31,30,31,31,30,31,30,31};
	while(~scanf("%d",&n)){
		for(int i=0;i<n;i++){
			int total=0;
			months[1]=28;
			scanf("%d %d %d",&year,&month,&day);
			if(year%4==0 && year%100!=0 || year%400==0){
				months[1]=29;
			}
			for(int j=2;j<year-1990+2;j++){
				if(j%4==0) total+=366;
				else total+=365;
			}
			for(int j=0;j<month-1;j++){
				total+=months[j];
			}
			total+=day-1;
			total%=5;
			if(total==3 || total==4){
				printf("He was basking on %d.%d.%d\n",year,month,day);
			}
			else printf("He was fishing on %d.%d.%d\n",year,month,day);
		}

	}
}