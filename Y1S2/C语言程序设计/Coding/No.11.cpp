#include<stdio.h>
#include<math.h>

int main(){
	int hour,min;
	scanf("%d %d",&hour,&min);
	float b,angle=0;
	b=(hour+(float)min/60)*30.0;
	angle=min*6.0;
	angle=fabs(b-angle);
	if(angle>180) angle=360-angle;
	printf("At %d:%02d the angle is %.1f degrees.\n",hour,min,angle);
	return 0;
}