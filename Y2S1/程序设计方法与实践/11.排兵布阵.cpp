#include<stdio.h>
#include<stdlib.h>

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

long long iX[100010] = {0};
long long iY[100010] = {0};
long long iM[100010] = {0};
int main(){

	long long iDisX = 0, iDisY = 0;
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++){
		scanf("%lld %lld", &iX[i], &iY[i]);
	}
	
	qsort(iX, n, sizeof(long long), compare);
	qsort(iY, n, sizeof(long long), compare);
	
	for(int i = 0; i < n; i++){
		iM[i] = iX[i] - i;
	}
	qsort(iM, n, sizeof(long long), compare);
	
	for (int i = 0; i < n; i++){
		if (iY[i] - iY[n / 2] >= 0)
			iDisY += iY[i] - iY[n / 2];
		else
			iDisY += iY[n / 2] - iY[i];

		if (iX[i] - (iM[n / 2] + i) >= 0)
			iDisX += iX[i] - (iM[n / 2] + i);
		else
			iDisX += (iM[n / 2] + i) - iX[i];
	}
	
	printf("%lld\n", iDisX + iDisY);
	return 0;
}
