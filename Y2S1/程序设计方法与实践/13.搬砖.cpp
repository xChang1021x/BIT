#include<stdio.h>

long long iSort[300010] = {0};
long long iNum[300010] = {0};

void GuiBingPaiXu(int iStart, int iEnd, long long *p){
	if(iStart >= iEnd){
		return;
	}
	int len = iEnd - iStart, mid = len / 2 + iStart;
	int iStartA = iStart, iEndA = mid;
	int iStartB = mid + 1, iEndB = iEnd;
	GuiBingPaiXu(iStartA, iEndA, p); //继续将元素拆解直到剩一个
	GuiBingPaiXu(iStartB, iEndB, p);
	int k = iStart;
	//进行排序
	while (iStartA <= iEndA && iStartB <= iEndB){
		if (iNum[iStartA] <= iNum[iStartB]){
			iSort[k++] = iNum[iStartA++];
		}
		else{ //如果为后半部分往前移，则计算前面有几个数
			*p += mid + 1 - iStartA;
			iSort[k++] = iNum[iStartB++];
		}
	}
	//当两个都未取完时，互相比对，较小先进
	
	while (iStartA <= iEndA){
		iSort[k++] = iNum[iStartA++];
	}
	while (iStartB <= iEndB){
		iSort[k++] = iNum[iStartB++];
	}
	//B取完就将A依次放入，反则亦然
	
	for (k = iStart; k <= iEnd; k++){
		iNum[k] = iSort[k];
	}
	//将当前排好的元素复制到原题
}

int main(){
	long long n;
	long long ans = 0;
	scanf("%d",&n);
	for (int i = 0; i < n; i++){
		scanf("%lld",&iNum[i]);
	}
	GuiBingPaiXu(0, n-1, &ans);

	printf("%lld\n",ans);
}