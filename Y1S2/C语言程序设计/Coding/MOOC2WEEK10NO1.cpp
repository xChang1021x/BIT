#include <stdio.h>

int main()
{     
    char op;
    int i,a,b;
    scanf("%d%c%d",&a,&op,&b);
    switch(op)
    {
        case '+':printf("%d",a+b);break;
        case '-':printf("%d",a-b);break;
        case '*':printf("%d",a*b);break;
        case '/':printf("%d",a/b);break;                
    }
    return 0;
}