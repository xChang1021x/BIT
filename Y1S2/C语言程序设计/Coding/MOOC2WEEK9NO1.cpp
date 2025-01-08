#include <stdio.h>
#include <string.h>

int main(void)
{	
	char str[300];
	gets(str);
	char* p = str;
	while (*p) {
		if (*p != 'n') putchar(*p);
		else if(*(p-1)!='n') putchar('\n');
		p++;		
	}
	return 0;
}