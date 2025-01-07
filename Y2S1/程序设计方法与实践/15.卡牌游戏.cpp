#include<stdio.h>

int main(){
	int n, k = 1, iLocateOne = -1, iLocateLastNum = 0;
	int sum = 0, iMove = 0;
	int iSumZero = 0;
	int iLastSmallest = 1000000000;
	int flag = 0, flag3;
	int iHandCard[200010] = {0}, iAreaCard[200010] = {0};
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%d", &iHandCard[i]);
	for(int i = 0; i < n; i++){
		scanf("%d", &iAreaCard[i]);	
		
		if (iAreaCard[i] == 1){
			iLocateOne = i;
			flag = 1;
		}
		if (flag && iAreaCard[i] == k){
			k++;
		}
		else
			flag = 0;
	}
	k--;
	if (k == 0){
		k = 1;
	}
	flag3 = -1;
	if (iAreaCard[n-1] != k){
		for (int i = iLocateOne + 1; i < n; i++){
			if (iAreaCard[i] - (i - iLocateOne) >= 1){
				sum++;
				iLocateLastNum = i;
				flag3 = i;
			}
			else if(iAreaCard[i] == 0){
				iSumZero++;
			}
			else{
				if (i - 1 != flag3)
					iMove = 1 - (iAreaCard[i] - (i - iLocateOne)) > iMove? 1 - (iAreaCard[i] - (i - iLocateOne)) : iMove;
			
			}		
		}
		if (sum + iSumZero == n - iLocateOne - 1){
			printf("%d\n", n + iLocateOne + 1);
		}
		else{
			printf("%d\n", iLocateOne + 1 + iMove + n);
		}

	}
	else{
		k++;
	
		for (int i = 0; i < iLocateOne; i++){
			if (iAreaCard[i] - i > k){
				sum ++;
				iLocateLastNum = i;
			}
			else if(iAreaCard[i] == 0){
				iSumZero++;
			}
		}
		if (sum + iSumZero == iLocateOne){
			printf("%d\n", n - k + 1);
		}
		else{
			printf("%d\n", 2*n - (n-1-iLocateOne));
		}				
	}	
}



//3
//0 3 0
//0 2 1
//
//4
//0 3 4 0
//0 2 1 0    = 7
//
//3
//0 3 0
//2 0 1    =  6
//
//6
//3 4 0 0 0 0
//5 6 0 0 1 2 = 4
//
//0 1 2 3 4 5
//
//7
//4 3 0 0 0 0 0
//5 6 7 0 0 1 2 = 5
//
//6
//1 4 0 0 0 0 
//6 3 2 5 0 0  = 8

//6
//2 5 0 0 0 0
//1 3 4 6 0 0  = 7

//5
//0 0 0 0 0 
//1 4 3 2 5
