#include<stdio.h>

int main(){
	int x,y,z;
	scanf("%d %d %d",&x,&y,&z);
	if(x+y>z && x+z>y && y+z>x){
		if(x==y && y==z){
			printf("equilateral triangle.\n");
		}
		else if((x==y)+(y==z)+(x==z)==1){
			printf("isoceles triangle.\n");
		}
		else printf("triangle.\n");
	} 
	else printf("non-triangle.\n");
	return 0;
}