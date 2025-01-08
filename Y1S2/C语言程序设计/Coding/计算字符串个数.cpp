#include <stdio.h>  
  
int countsub( char *str, char *ss );  
  
main( )  
{  
    char s1[1000] = {0}, s2[100] = {0};  
    gets(s1);  
    gets(s2);  
    printf("%d\n", countsub( s1, s2 ) );  
}  

int countsub(char *str,char *ss){
	int i=0,j=0;
	char *p=str,*q=ss;
	while(*p!='\0')
	{
		q=ss;
		if(*q==*p)
		{
			while(*q++==*p++)
			{
				if(*q=='\0')
				{
					++i;
					q=ss;
				}
			}
			if(i>=j)
			{
				j=i;
				i=0;
			}
		}
		else
		{
			p++;
		}
	}
	return j;
}