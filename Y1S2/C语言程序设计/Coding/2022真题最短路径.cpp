#include<stdio.h>

long long int jc(int x)
{
	if(x>1) return x*jc(x-1);
	else return 1;
}

long long int hc(int x,int y)
{
	if(x>y) return x*hc(x-1,y);
	else return 1;
}

int main()
{
	int m,n,p,q;
	int sum1,sum2;
	int x=0,y=0;
	scanf("%d %d %d %d",&m,&n,&p,&q);
	sum1 = hc(p+q,p)/jc(q);
	sum2 = hc(m+n-p-q,m-p)/jc(n-q);
	printf("%lld\n",sum1*sum2);
	while(x!=m || y!=n+1)
	{
		if(x<p) printf("(%d,%d)",x++,y);
		else if(y<q) printf("(%d,%d)",x,y++);
		else if(x<m) printf("(%d,%d)",x++,y);
		else printf("(%d,%d)",x,y++);
	}
	printf("\n");
}