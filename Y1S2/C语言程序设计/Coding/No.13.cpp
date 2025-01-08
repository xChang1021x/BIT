#include<stdio.h>
#include<math.h>

int main(){
	int a,b,c;
	double x1,x2;
	while(~scanf("%d %d %d",&a,&b,&c)){
		if(a==0 && b==0){
			printf("Input error!\n");
			continue;
		}
		if(a!=0){
			if(b*b-4*a*c<0){
				if(b==0){
					printf("x1=%lfi\n",sqrt(4*a*c-b*b)/(2*a));
					printf("x2=-%lfi\n",sqrt(4*a*c-b*b)/(2*a));
				}
				else{
					printf("x1=%lf+%lfi\n",-b/(2.0*a),sqrt(4*a*c-b*b)/(2*a));
					printf("x2=%lf-%lfi\n",-b/(2.0*a),sqrt(4*a*c-b*b)/(2*a));	
				}
			}
			else if(b*b-4*a*c==0){
				x1=(-b+sqrt(b*b-4*a*c))/(2*a);
				if(x1==0)	
					printf("x1=x2=%lf\n",fabs(x1));
				else printf("x1=x2=%lf\n",x1);
				
			}
			else{
				x1=(-b+sqrt(b*b-4*a*c))/(2*a);
				x2=(-b-sqrt(b*b-4*a*c))/(2*a);
				if(x1==0) x1=fabs(x1);
				if(x2==0) x2=fabs(x2);
				printf("x1=%lf\n",x1);
				printf("x2=%lf\n",x2);
			}
		}
		else{
			x1=-(double)c/b;
			if(x1==0) printf("x=%lf\n",fabs(x1));
			else printf("x=%lf\n",x1);
		}
	}
	
}