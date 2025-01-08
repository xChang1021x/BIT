#include<stdio.h>
int main()
{
	FILE * fp;
	int n,flag=0;
	char filename[20],ch[20];
	scanf("%s",filename);
	scanf("%d",&n);
	if(n==2) flag=1;
	if((fp=fopen(filename,"r"))==NULL)
		printf("File Name Error.\n");
	else if(n>4)
		printf("Line No Error.\n");
	else {
		while(--n)
	{
		fgets(ch,19,fp);
	}
	fgets(ch,19,fp);
	if(flag) printf("%s\n",ch);
	else printf("%s",ch);
			}
}