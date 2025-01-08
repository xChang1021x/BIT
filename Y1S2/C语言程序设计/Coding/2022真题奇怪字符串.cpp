#include<stdio.h>
#include<string.h>

int ans(int n, int k)
{
	if(n!=1)
	{	
		if(n % 2 != 0)
		{
			k++;
			n++;
		}
		k++;
		return ans(n/2,k); 
	}
	else return k;
}

int main(){
	int n,k,sum;
	scanf("%d %d",&n,&k);
	sum=ans(k,0);
	if(sum%2==0)
	{
		printf("0\n");
	}
	else
	{
		printf("1\n");
	}
}