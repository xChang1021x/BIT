#include <iostream>
using namespace std;

int Max = INT_MIN;
int zhishu[100000] = {0};
int x = 0;


int main()
{
  for (int i = 2; i < 100000; i++){
    if (x == 0) zhishu[x++] = i;
    else{
      for (int j = 0; j < x; j++){
        if (i % zhishu[j] == 0){
          break;
        }
        else if (j == x - 1){
          zhishu[x++] = i;
        }
      }
    }
  }

  int dp[100010] = {0};
  int n;
  cin >> n;
  int a[100010] = {0};
  for (int i = 0; i < n; i++){
    cin >> a[i];
  }
    
  for (int i = 0; i < n; i++){
    for (int j = 0; j < x; j++){
      int sum = 0;
      if (i + zhishu[j] >= n){
        break;
      }
      for (int k = 0; k < zhishu[j]; k++){
        sum += a[i+k];
      }
      if (sum > Max) Max = sum;
    }
  }

  cout << Max << endl;
  return 0;
}