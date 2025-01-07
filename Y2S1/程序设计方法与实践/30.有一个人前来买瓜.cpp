#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

struct Fruit{
	int weight;
	int ripeness;
	int gold;
}fruits[110];

struct Rule{
	int W;
	int V;
}rules[110];

long long dp[501][501];
 
int main(){
	int n, q;
	long long ans = 0;
	scanf("%d %d", &n, &q);
	memset(dp, -1, sizeof(dp));
	dp[0][0] = 0;
	
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d", &fruits[i].weight, &fruits[i].ripeness, &fruits[i].gold);	
	}
	for (int i = 0; i < q; i++){
		scanf("%d %d", &rules[i].W, &rules[i].V);
	}
	
	for (int i = 1; i <= n; i++){
		for (int j = 500; j >= 0; j--){
			for (int k = 500; k>= 0; k--){
				if (dp[j][k] < 0)
					continue;
					
				if (j + fruits[i].weight <= 500){
					dp[j + fruits[i].weight][min(k + fruits[i].ripeness, 500)] = max(dp[j][k] + fruits[i].gold, dp[j + fruits[i].weight][min(k + fruits[i].ripeness, 500)]);
				}
			}
		}
	} 
	
	for (int i = 0; i < q; i++){
		ans = -1;
		for (int j = 0; j <= rules[i].W; j++){
			for (int k = rules[i].V; k <= 500; k++){
				ans = max( ans, dp[j][k]);
			}
		}
		printf("%lld\n", ans);
	} 
	 
	return 0;
}