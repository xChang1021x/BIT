#include<iostream>
#include<algorithm>

using namespace std;

int len[100010] = {0};
int main(){
	int n, k;
	int flag = -1;
	int iTotalmin = 0, iTotalmax = 0, iTotalmid = 0;
	int max = 0, min = 1, mid = 0, sum = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%d", &len[i]);
		max = max > len[i] ? max : len[i];
	}
	mid = max / 2;
	scanf("%d", &k);
	while (min <= max){
		iTotalmin = 0;
		iTotalmax = 0;
		iTotalmid = 0;
		for (int i = 0; i < n; i++){
			iTotalmin += len[i] / min;
			iTotalmax += len[i] / max;
			iTotalmid += len[i] / mid;
		}
		if (iTotalmin < k){
			printf("%d\n", min-1);
			return 0;
		}
		if (iTotalmax >= k){
			printf("%d\n", max);
			return 0;
		}
		
		if (iTotalmid < k && flag == 1){
			printf("%d\n", mid-1);
			return 0;
		}
		if (iTotalmid >= k && flag == 0){
			printf("%d\n", mid);
			return 0;
		}
		
		if (iTotalmid >= k){
			mid++;
			flag = 1;
		}
		else{
			mid--;
			flag = 0;
		}
		
		min++;
		max--;
	}
	printf("0\n");
	return 0;
}
