#include<stdio.h>

int main(){
	double v0,a,t;
	double s;
	while(~scanf("%lf %lf %lf",&v0,&a,&t)){
		s=v0*t+a*t*t/2;
		printf("%.3lf\n",s);
	}
}