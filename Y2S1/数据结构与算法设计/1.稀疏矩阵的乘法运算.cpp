#include<iostream>

using namespace std;

typedef struct data{
	int row, col;
	int e;
} TRIPLE;

typedef struct group{
	TRIPLE data[1000];
	int m,n;
	int total;
} TPGROUP;

int getElement(int i, int j, TPGROUP AB){
	int x = 0;
	while(x < AB.total){
		if (AB.data[x].row == i && AB.data[x].col == j){
			return AB.data[x].e;
		}
		else{
			x++;
		}
		
		if (i < AB.data[x].row){
			break;
		}
	}
	return 0;
}

TPGROUP A;
TPGROUP B;
TPGROUP C;

int main(){
	scanf("%d %d %d", &A.m, &A.n, &A.total);
	for (int i = 0; i < A.total; i++){
		scanf("%d %d %d", &A.data[i].row, &A.data[i].col, &A.data[i].e);
	}
	scanf("%d %d %d", &B.m, &B.n, &B.total);
	for (int i = 0; i < B.total; i++){
		scanf("%d %d %d", &B.data[i].row, &B.data[i].col, &B.data[i].e);
	}
	
	C.total = 0;
	C.m = A.m;
	C.n = B.n;
	
	for (int i = 1; i <= A.m; i++){
		for (int j = 1; j <= B.n; j++){
			int sum = 0;
			for (int k = 1; k <= A.n; k++){
				sum += getElement(i, k, A) * getElement(k, j, B);
			}
			if (sum != 0){
				C.data[C.total].row = i;
				C.data[C.total].col = j;
				C.data[C.total].e = sum;
				C.total++;
			}
		}
	}
	
	printf("%d\n%d\n%d\n", C.m, C.n, C.total);
	for(int i = 0; i < C.total; i++){
		printf("%d,%d,%d\n", C.data[i].row, C.data[i].col, C.data[i].e);
	}
}