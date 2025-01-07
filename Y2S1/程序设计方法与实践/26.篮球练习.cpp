#include<iostream>
#include<algorithm>
#include<cstring>

int main(){
	int Block[25][25];
	long long Move[25][25] = {0};
	int x1, y1, x2, y2;
	
	memset(Block, 1, sizeof(Block));
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	
	Block[x2][y2] = 0;
	
	Block[x2+2][y2-1] = 0;
	Block[x2+2][y2+1] = 0;
	Block[x2-2][y2-1] = 0;
	Block[x2-2][y2+1] = 0;
	Block[x2-1][y2+2] = 0;
	Block[x2-1][y2-2] = 0;
	Block[x2+1][y2+2] = 0;
	Block[x2+1][y2-2] = 0;
	
	Move[0][0] = 1;
	
	if (x2 == 0 && y2 == 0){
		printf("0\n");
		return 0;
	}
	
	for (int i = 0; i <= x1; i++){
		for (int j = 0; j<= y1; j++){
			if (i == 0 && j == 0)
				continue;
			if (Block[i][j]){
				if (i > 0 && j > 0)
					Move[i][j] = Move[i - 1][j] + Move[i][j - 1];
				else if (i > 0)
					Move[i][j] = Move[i - 1][j];
				else
					Move[i][j] = Move[i][j - 1];
				
			}
		}
	}
	
	printf("%lld\n", Move[x1][y1]);
}