#include<stdio.h>
#include<stdlib.h>

int main()
{
	int t,i,day,e;
	int n;
	int a[200];
	scanf("%d",&t);
	for(i=1;i<=t;i++)
	{	
		scanf("%d",&n);
		a[i]=n;
	}
	for(i=1;i<=t;i++)
	{
		if(a[i]==1) printf("0\n");
		else
		{
			if(a[i]%2==0)
			{
				day=a[i]-1;printf("%d\n",day);
			}
			else
			{
				day=a[i];printf("%d\n",day);
			}
		}
	}
	return 0;
}