#include<stdio.h>  
  
int main(){  
	int d,y,k=0,f,ia;  
	int month[15]={0,31,28,31,30,31,30,31,31,30,31,30};  
	char p[5][10]={"Friday","Fridays","is","are"};  
	int a[15]={0};  
	int sumd=0;  
	scanf("%d",&y);  
	if(y%4==0 && y%100!=0 || y%400==0)  
	{  
		month[2]=29;  
	}	  
	sumd=(y-1+(y-1)/4-(y-1)/100+(y-1)/400+13);  
	for(int j=1;j<13;++j)  
	{  
		sumd+=month[j-1];  
		if(sumd%7==5)  
		{  
			a[k++]=j;  
		}  
	}  
	if(k==1)  
	{  
		f=0;  
		ia=2;  
	}  
	else if(k>1)  
	{  
		f=1;  
		ia=3;  
	}  
	else  
	{  
		f=1;  
		ia=2;  
	}  
	printf("There %s %d Black %s in year %d.\n",p[ia],k,p[f],y);  
	if(k>1) printf("They are:\n");  
	else printf("It is:\n");  
	for(int j=0;j<k;j++){  
		printf("%d/%d/13\n",y,a[j]);
	}
}  