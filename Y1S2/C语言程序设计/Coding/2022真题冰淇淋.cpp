#include<stdio.h>

int main(){
	int m,n,o;
	scanf("%d %d %d",&m,&n,&o);
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<(4*(m-1)+n)/2-i;j++)
		{
			printf(" ");	
		}
		for(int j=0;j<2*i+1;j++)
		{
			printf("*");
		} 
		printf("\n");
	}
	for(int i=0;i<m;i++)
	{
		for(int k=0;k<o;k++)
		{
			for(int j=0;j<(m-1)*2-i*2;j++)
			{
				printf(" ");
			}
			for(int j=0;j<n+i*4;j++)
			{
				printf("*");
			}
			printf("\n");			
		}
	}
	for(int i=0;i<(4*(m-1)+n)/2+1;i++)
	{
		for(int j=0;j<4*(m-1)+n-i;j++)
		{
			if(j==i || j==4*(m-1)+n-i-1)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}