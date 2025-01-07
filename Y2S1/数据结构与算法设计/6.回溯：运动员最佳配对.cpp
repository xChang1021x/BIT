#include<iostream>

using namespace std;

int n;
int Result = 0;
int P[15][15] = {0};
int Q[15][15] = {0};
int flagQ[15] = {0};
int PQ[15][15] = {0};
int Max[15] = {0};

void Solve(int x, int sum){
	if (x >= n){
		if (sum > Result){
			Result = sum;
		}		
	}
	
	int max = 0;
	for (int i = x; i < n; i++){
		max += Max[i];
	}
	if (sum + max < Result)
		return;
	
	for (int i = 0; i < n; i++){
		if (flagQ[i] == 1){
			continue;
		}
		else{
			flagQ[i] = 1;
			sum += P[x][i]*Q[i][x];
			Solve(x+1, sum);
			flagQ[i] = 0;
			sum -= P[x][i]*Q[i][x];	
		}
	}

}

int main(){
	cin >> n;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cin >> P[i][j];
		}
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cin >> Q[i][j];
		}
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			PQ[i][j] = P[i][j] * Q[j][i];
			Max[i] = max(PQ[i][j], Max[i]);
		}
	}
	Solve(0, 0);
	cout << Result << endl;
}