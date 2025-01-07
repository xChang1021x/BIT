#include <iostream>
#include <algorithm>

using namespace std;

int main(){
	int n;
	int triangle[110][110] = {0};
	cin >> n;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < i + 1; j++){
			cin >> triangle[i][j];
		}
	}
	for (int i = n-2; i >= 0; i--){
		for (int j = 0; j < i+1; j++){
			triangle[i][j] = max(triangle[i][j]+triangle[i+1][j], triangle[i][j]+triangle[i+1][j+1]);
		}
	}
	cout << triangle[0][0] << endl;
	return 0;
}