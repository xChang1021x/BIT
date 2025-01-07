#include<stdio.h>
#include<string.h>

#define LEFT 0
#define RIGHT 1
#define MARK 2

int iSumLeft[100010] = {0};
int iSumRight[100010] = {0};
int main(){
	memset(iSumLeft, -1, sizeof(iSumLeft));
	memset(iSumRight, -1, sizeof(iSumRight));
	int n, len, sum = 0, min;
	int maxLeft = 0, maxRight = 0, max = 0;
	int iCntLeftRight[100010][3] = {0};
	char A[100010] = {0};
	char *p;
	scanf("%d",&n);
	getchar();
	for (int i = 0; i < n; i++){
		scanf("%s",A);
		p = A;
		while (*p != 0){
			if (*p == '('){
				iCntLeftRight[i][RIGHT]++;
			}
			else if (*p == ')'){
				if (iCntLeftRight[i][RIGHT] == 0){
					iCntLeftRight[i][LEFT]++;
				}
				else{
					iCntLeftRight[i][RIGHT]--;
				}				
			}
			p++;
		}
		maxLeft = maxLeft > iCntLeftRight[i][LEFT] ? maxLeft : iCntLeftRight[i][LEFT];
		maxRight = maxRight > iCntLeftRight[i][RIGHT] ? maxRight : iCntLeftRight[i][RIGHT];
	}
	max = maxLeft > maxRight ? maxRight : maxLeft;
	for (int i = 0; i < n; i++){
		if (iCntLeftRight[i][LEFT] != 0 && iCntLeftRight[i][RIGHT] != 0){
			continue;
		}
		else if (iCntLeftRight[i][LEFT] != 0){
			iSumLeft[iCntLeftRight[i][LEFT]]++;
		}
		else if (iCntLeftRight[i][RIGHT] != 0){
			iSumRight[iCntLeftRight[i][RIGHT]]++;
		}
		else
			sum++;
	}
	sum /= 2;
	for (int i = 0; i <= max; i++){
		if (iSumLeft[i] == -1 || iSumRight[i] == -1){
			continue;
		}
		else {
			min = iSumLeft[i] < iSumRight[i] ? iSumLeft[i] : iSumRight[i];
			min++;
			sum += min;
		}
	}
	
	
	printf("%d\n",sum);
}

//		printf("%d %d\n",iCntLeftRight[i][LEFT], iCntLeftRight[i][RIGHT]);
