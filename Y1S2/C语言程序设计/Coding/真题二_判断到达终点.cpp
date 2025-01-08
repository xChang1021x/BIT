#include<stdio.h>

int finish(int x, int y, int p, int q, int k)
{	
	if(x!=p || y!=q)
	{
		if(x+y<=p && x!=p && y!=0)
		{
			k=finish(x+y,y,p,q,k);
		}
		if(x+y<=q && y!=q && x!=0 && k!=1)
		{
			k=finish(x,x+y,p,q,k);
		}
		if(k==1) return 1;
		return 0;
	}
	return 1;
}

int main()
{
	int a1,b1,a2,b2;
	scanf("%d,%d %d,%d",&a1,&b1,&a2,&b2);
	if(a1==0 && b1==0 && a2!=0 && b2!=0)
	{
		printf("No.\n");
		return 0;
	}
	if(finish(a1,b1,a2,b2,0))
	{
		printf("Yes.\n");
	}
	else
	{
		printf("No.\n");
	}		
}
