#include<stdio.h>

int main(){
	int a,b,x,y;
	int min,fenzi,fenmu;
	char o;
	scanf("%d/%d %c %d/%d",&a,&b,&o,&x,&y);
	if(o=='+'){
		fenzi=a*y+x*b;
		fenmu=b*y;
	}
	else if(o=='-'){
		fenzi=a*y-x*b;
		fenmu=b*y;
	}
	else if(o=='*'){
		fenzi=a*x;
		fenmu=b*y;
	}
	else if(o=='/'){
		fenzi=a*y;
		fenmu=b*x;
	}
	if(fenmu<fenzi){
		min=fenmu;
	}
	else min=fenzi;
	for(int i=min;i>1;i--){
		if(fenzi%i==0 && fenmu%i==0){
			fenzi/=i;
			fenmu/=i;
			break;
		}
	}
	if(fenzi%fenmu==0) printf("%d/%d %c %d/%d = %d\n",a,b,o,x,y,fenzi/fenmu);
	else if(fenzi!=0) printf("%d/%d %c %d/%d = %d/%d\n",a,b,o,x,y,fenzi,fenmu);
	else printf("%d/%d %c %d/%d = 0\n",a,b,o,x,y);
}