#include<stdio.h>

int main(){
	int m,q,v,b;
	int x,y,z;
	double r;
	while(~scanf("%d %d %d %d",&m,&q,&v,&b)){
		z=0;
		scanf("%d %d",&x,&y);
		r=(double)m*v/q/b;
		printf("%.2lf ",r);
		if(x&&y==1){
			z=0;
		}
		else z=1;
		if((x||y)&&z){
			printf("1\n");
		}
		else printf("0\n");
	}
}