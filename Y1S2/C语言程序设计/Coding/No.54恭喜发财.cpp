#include <stdio.h>
#include <string.h>

struct ren
{
	char name[15];
	int money;
};

int main()
{
	int n,i,j,k,m,qian=0,shu=0;
	char name[15];
	struct ren list[10];
	scanf("%d",&n);
	for (i=0;i<n;i++)
	{
		scanf("%s",list[i].name);
		list[i].money=0;
	}
	for (i=0;i<n;i++)
	{
		scanf("%s %d %d",name,&qian,&shu);
		if (shu!=0)
		{
			for (k=0;k<n;k++)
			{
				if (strcmp(name,list[k].name)==0)
					list[k].money-=(qian/shu)*shu;
			}
    		for (m=0;m<shu;m++)
    		{
    			scanf("%s",name);
    			for (j=0;j<n;j++)
    			{
    				if (strcmp(name,list[j].name)==0)
						list[j].money+=qian/shu;
				}
			}
		}
	}
	for (i=0;i<n;i++)
		printf("%s %d\n",list[i].name,list[i].money);
	return 0;
}