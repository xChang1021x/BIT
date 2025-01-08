#include <stdio.h>

int f(int x,int y)
{
	int a,b;
	if(x==1||y==1||x*y==0) return 1;
	else
	{
		a=x/y;b=x-a*y;
		if(a==1) return f(b,b)+f(x,y-1);
		else return f(x-y,y)+f(x,y-1);
	}
}

int main()
{
	int m,n,c;
	scanf("%d %d",&m,&n);
	printf("%d\n",f(m,n));
}