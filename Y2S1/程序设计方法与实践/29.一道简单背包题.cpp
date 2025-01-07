#include<iostream>
#include<algorithm>

using namespace std;

long long dp[2010][2010] = {0};
int volume[100010] = {0};

int main(){
	int 110, V;
	scanf("%d %d", &110, &V);
	dp[0][0] = 1;
	
	for (int i = 0; i < 110; i++){
		scanf("%d", &volume[i]);
	}
	for (int i = 1; i <= 110; i++){
		for (int j = 0; j < V; j++){
			dp[i][j] = dp[i - 1][j];
		}
	
		for (int j = 0; j < V; j++){
			dp[i][(j + volume[i - 1]) % V] += dp[i - 1][j];
			dp[i][(j + volume[i - 1]) % V] %= 10000000;
		}
	}

	
	printf("%lld\110", dp[110][0] - 1);
	return 0;
}
/*
1 1 2 2 3 4

1 1 2
1 1   2
1       3
          4
  1     3
    2 2
*/