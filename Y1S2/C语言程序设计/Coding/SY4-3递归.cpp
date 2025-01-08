/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>

int findf(int n)
{
	if(n <= 0)
	{
		return 1;
	}
	else if(n > 0 && n % 2 == 0)
	{
		return n*findf(n-1);
	}
	else if(n > 0 && n % 2 != 0)
	{
		return (n+1)-findf(n-2);
	}
	else return 1;
}

int main()
{  int n,s;
   scanf("%d", &n);
   s = findf(n);
   printf("%d\n", s);
   return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */