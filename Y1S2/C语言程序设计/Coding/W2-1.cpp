#include<stdio.h>

int main(){
	double a,b,c;
	scanf("%lf %lf %lf",&a,&b,&c);
	printf("%.2lf %.2lf %.2lf\n",a,b,c);
	printf("%.2lf\n",a+b+c);
	printf("%d\n",(int)(a+b+c+0.5));
	return 0;
}