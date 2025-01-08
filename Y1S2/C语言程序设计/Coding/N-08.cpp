#include<stdio.h>
#include<math.h>

int main(){
	double m,r;
	double v;
	const double G=6.67e-11;
	while(~scanf("%lf %lf",&m,&r)){
		v=sqrt(G)*sqrt(m)/sqrt(r);
		printf("%e\n",v);
	}
}