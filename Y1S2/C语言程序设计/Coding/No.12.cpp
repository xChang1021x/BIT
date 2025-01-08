#include<stdio.h>
#include<ctype.h>

int main(){
	char a;
	while(~scanf("%c",&a)){
		getchar();
		if(a>=65 && a<=90){
			a=tolower(a);
		}
		else if(a>=97 && a<=122){
			a=toupper(a);
		}
		printf("%c\n",a);
	}
	return 0;
}