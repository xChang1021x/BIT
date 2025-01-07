#include <iostream>
#include <algorithm>

using namespace std;

struct Timu {
    int time;
    int score;
} question[30];

int maxScore(int n, int m) {
    int dp[30][30010] = {0}; 
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (question[i - 1].time <= j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - question[i - 1].time] + question[i - 1].time * question[i - 1].score);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[m][n];
}

int main() {
    int n, m;
    int result;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
    	scanf("%d %d", &question[i].time, &question[i].score);
    }
    result = maxScore(n, m);
    printf("%d\n", result);
    return 0;
}
