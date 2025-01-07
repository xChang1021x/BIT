#include <stdio.h>

long long iStart[300010] = {0};
long long iEnd[300010] = {0};

void swap(long long *x, long long *y){
	long long t = *x;
	*x = *y;
	*y = t;
}
void KuaiSuPaiXu(int l, int r){
	if(l >= r) return;
	int key = iEnd[l], i = l, j = r;
	while(i < j){
		while(iEnd[j] >= key && i < j)
			j--;		
		while(iEnd[i] <= key && i < j)
			i++;

		swap(&iEnd[i],&iEnd[j]);
		swap(&iStart[i],&iStart[j]);
	}
	swap(&iEnd[l],&iEnd[i]);
	swap(&iStart[l],&iStart[i]);
	KuaiSuPaiXu(l,i-1);
	KuaiSuPaiXu(i+1,r);
}

int main(){
	int n;
	long long max = 0;
	int iPre = 0;
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++){
		scanf("%lld %lld", &iStart[i], &iEnd[i]);
	}

	KuaiSuPaiXu(1, n);

	for (int i = 1; i <= n; i++){
		if (iStart[i] >= iPre){
			max++;
			iPre = iEnd[i];
		}
	}
		
	printf("%lld\n",max);

	return 0;
}