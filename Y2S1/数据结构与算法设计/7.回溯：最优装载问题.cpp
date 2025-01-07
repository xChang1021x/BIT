#include<iostream>
#include<cstring>

using namespace std;

int c;
int n;
int Max = 0;
int sum = 0;
int w[110] = {0};
int TanxinMax[110] = {0};
int TanxinMin[110] = {0};
int Result[110] = {0};
int Choose[110] = {0};

void Solve(int Start){
	
	if (sum > c)
		return;	
		
	if (Max <= c){
		if (Max < sum){
			Max = sum;
			memcpy(Result, Choose, sizeof(Choose));
		}
	}	
	
	if (sum + TanxinMax[Start] < Max || sum + TanxinMin[Start] > c)
		return;
	
	for (int i = Start; i < n; i++){
		Choose[i] = 1;
		sum += w[i];
		Solve(i+1);
		sum -= w[i];
		Choose[i] = 0;
	}
}

int main(){
	int total = 0;
	cin >> c >> n;
	for (int i = 0; i < n; i++){
		cin >> w[i];
		total += w[i];
	}
	TanxinMax[0] = total;
	for (int i = 1; i < n; i++){
		TanxinMax[i] = TanxinMax[i-1] - w[i-1];
	}
	for (int i = 0; i < n; i++){
		TanxinMin[i] = w[i];
		for (int j = i+1; j < n; j++){
			TanxinMin[i] = min(TanxinMin[i], w[j]);
		}
	}
	Solve(0);
	cout << Max << endl;
	for (int i = 0; i < n; i++){
		if (Result[i] != 0){
			cout << i+1 << " ";
		}
	}
	cout << endl;
}