#include<stdio.h>
#include<math.h>

int main(){
	double x1,x2,y1,y2;
	double result;
	scanf("(%lf,%lf) (%lf,%lf)",&x1,&y1,&x2,&y2);
	result=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
	printf("%.2lf\n",sqrt(result));
	return 0;
}