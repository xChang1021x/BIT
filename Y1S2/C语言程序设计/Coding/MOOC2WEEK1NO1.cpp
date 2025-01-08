#include<stdio.h>

int fun1(int a, int b){
	int i,t;
	if(a>b){
		t=a;
		a=b;
		b=t;
	}
	for(i=a;i>0;i--){
		if(a%i==0 && b%i==0) return i;
	}
	return i;
}

int fun2(int a, int b, int x){
	return a*b/x;
}

int main(){
	int a,b;
	int x,y;
	scanf("%d,%d",&a,&b);
	x=fun1(a,b);
	y=fun2(a,b,x);
	printf("最大公约数：%d\n最小公倍数：%d\n",x,y);
}