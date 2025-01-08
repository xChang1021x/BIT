#include<stdio.h>

int main()
{
	int n,x,y,k;
	char a;
	scanf("%d %c",&n,&a);
	char A[100][100]={0};
	if(n==1)
	{
		printf("%c\n",a);
		return 0;
	}
	for(int i=0;i<2*n-1;i++)
	{
		for(int j=0;j<2*n-1;j++)
		{
			A[i][j]=' ';
		}
	}
	x=0;
	y=n-1;
	for(int i=0;i<4*n-4;i++)
	{
		if(i<n-1)
		{
			A[x++][y--]=a;
			a++;
			if(a>'Z') a-=26;
		}
		else if(i<2*n-2)
		{
			A[x++][y++]=a;
			a++;
			if(a>'Z') a-=26;
		}
		else if(i<3*n-3)
		{
			A[x--][y++]=a;
			a++;
			if(a>'Z') a-=26;
		}
		else
		{
			A[x--][y--]=a;
			a++;
			if(a>'Z') a-=26;
		}
	}
	
	for(int i=0;i<2*n-1;i++)
	{
		for(int j=0;j<2*n-1;j++)
		{
			if(A[i][j]>='A' && A[i][j]<='Z')
			{
				k=j;
			}
		}
		for(int j=0;j<k+1;j++)
		{
			printf("%c",A[i][j]);
		}
		printf("\n");
	}
}