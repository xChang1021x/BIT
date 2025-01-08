#include <stdio.h>
#include<string.h>
#define N 256

int main()
{
    char str[N]="",*p = str;
    gets(str);
    p += strlen(str) - 1;
    while(*p)
        putchar(*p--);
    return 0;
}