#include <iostream>
#include <algorithm>

using namespace std;

long long dp[2010][2010] = {0};

int main(){
	int n;
	long long ans = 0;
	long long Location[2010] = {0};

	
	scanf("%d", &n);
	for (int i = 0; i <= n; i++){
		scanf("%d", &Location[i]);
	}
	dp[1][Location[0]] = 1;
	dp[1][Location[1]] = 1;		
	
	for (int i = 2; i <= n; i++){
		for (int j = i - 2; j >= 0; j--){
			dp[i][Location[i]] = 1;
			if (dp[i - 1][Location[j]] != 0){
				if (Location[i] > Location[i - 1] && Location[i] > Location[j]){
					dp[i][min(Location[i - 1], Location[j])] += dp[i - 1][Location[j]];
					dp[i][min(Location[i - 1], Location[j])] %= 2147483647;
				}
				else if (Location[i] < Location[i - 1] && Location[i] < Location[j]){
					dp[i][max(Location[i - 1], Location[j])] += dp[i - 1][Location[j]];
					dp[i][max(Location[i - 1], Location[j])] %= 2147483647;
				}
				else if ((Location[i] <= Location[i - 1] && Location[i] >= Location[j]) || (Location[i] >= Location[i - 1] && Location[i] <= Location[j])){
					dp[i][Location[i - 1]] += dp[i - 1][Location[j]];
					dp[i][Location[i - 1]] %= 2147483647;
					dp[i][Location[j]] += dp[i - 1][Location[j]];
					dp[i][Location[j]] %= 2147483647;
					
				}
			}
		}
	}
	for (int i = 0; i <= 2000; i++){
		ans += dp[n][i];
		ans %= 2147483647;
	}
	printf("%lld\n",ans - 1);
	return 0;
}