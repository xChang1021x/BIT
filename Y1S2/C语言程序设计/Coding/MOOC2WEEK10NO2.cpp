#include <stdio.h>
#include <ctype.h>
double expression_value();
double  term_value();
double  factor_value();
double  expression_value()
{
    double  result=term_value();
    while(1)
    {
        char op = getc(stdin);
        ungetc(op, stdin);
        if(op=='+'||op=='-')
        {
            getchar();
            double  value=term_value();
            if(op=='+')
                result+=value;
            else
                result-=value;
        }
        else
            break;
    }
    return result;
}
double  term_value()
{
    double  result = factor_value();
    while(1)
    {
        char c= getc(stdin);
        ungetc(c, stdin);
        if(c=='*'||c=='/')
        {
            getchar();
            double  value = factor_value();
            if(c=='*')
                result*=value;
            else
                result/=value;
        }
        else
            break;
    }
    return result;
}
double  factor_value()
{
    double  result=0;
    char c= getc(stdin);
    ungetc(c, stdin);
    if(c=='(')
    {
        getchar();
        result = expression_value();
        getchar();
    }
    else
    {
        while(isdigit(c))
        {
            result = 10*result+c-'0';
            getchar();
            c = getc(stdin);
            ungetc(c, stdin);
        }
        if(c=='.')
        {
            getchar();
            c = getc(stdin);
            ungetc(c, stdin);
            double t=0.1;
            while(isdigit(c))
            {
                result += (c-'0')*t;
                t*=0.1;
                getchar();
                c = getc(stdin);
                ungetc(c, stdin);
            }
        }
    }
    return result;
}
int main()
{
    printf("%.f\n",expression_value());
    return 0;
}