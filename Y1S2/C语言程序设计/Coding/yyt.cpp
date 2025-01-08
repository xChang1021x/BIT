#include<stdio.h>
#include<string.h>

int main(){
	char a[5][100];
	int k=0;
	for(int i=0;i<2;++i)
	{
		scanf("%s",&a[i]);
	}
	int i=0;
	while(i<strlen(a[0]) && k<strlen(a[1]))
	{
		if(a[0][i]>=a[1][k])
		{
			printf("%c",a[1][k++]);
		}
		else
		{
			printf("%c",a[0][i++]);
		}
	}
	for(int j=i;j<strlen(a[0]);++j)
	{
		printf("%c",a[0][j]);
	}
	for(int i=k;i<strlen(a[1]);++i)
	{
		printf("%c",a[1][i]);
	}
	printf("\n");
	return 0;
}