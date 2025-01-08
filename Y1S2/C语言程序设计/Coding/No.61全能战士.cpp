#include<stdio.h>

int main()
{
	int n,n1,n2,n3,n12,n13,n23;
	scanf("%d %d %d %d %d %d %d",&n,&n1,&n2,&n3,&n12,&n13,&n23);
	printf("%d\n",n-n1-n2-n3+n12+n23+n13);
	return 0;
}