#include<iostream>

using namespace std;

int n, m;
int sum = 0;
int choose = 0;
int Map[15][15] = {0};

void ControlMap(int Start, int x){
	for (int i = 0; i < n; i++){
		Map[Start][i]++;
		Map[i][x]++;
		if (Start-i >= 0){
			if (x-i >= 0 && i != 0)
				Map[Start-i][x-i]++;
			if (x+i < n && i != 0)
				Map[Start-i][x+i]++;
		}
		if (Start+i < n){
			if (x-i >= 0 && i != 0)
				Map[Start+i][x-i]++;
			if (x+i < n && i != 0)
				Map[Start+i][x+i]++;
		}
	}
	Map[Start][x]--;
}

void ReverseMap(int Start, int x){
	for (int i = 0; i < n; i++){
		Map[Start][i]--;
		Map[i][x]--;
		if (Start-i >= 0){
			if (x-i >= 0 && i != 0)
				Map[Start-i][x-i]--;
			if (x+i < n && i != 0)
				Map[Start-i][x+i]--;
		}
		if (Start+i < n){
			if (x-i >= 0 && i != 0)
				Map[Start+i][x-i]--;
			if (x+i < n && i != 0)
				Map[Start+i][x+i]--;
		}
	}
	Map[Start][x]++;	
}

bool Check(){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (Map[i][j] == 0)
				return false;
		}
	}
	return true;
}

void Solve(int Start, bool flag){
	
	if (choose == m){
		bool flag;
		flag = Check();
		if(flag){
			sum++;
		}
		return;
	}
	
	if (Start >= n)
		return;
		
	if (!flag){
		Solve(Start+1, true);
		Solve(Start+1, false);
	}
	else{
		for (int i = 0; i < n; i++){
			if (Map[i][j] == 0){
				
			}
		}
	}
				

}

int main(){
	cin >> n >> m;
	Solve(0, 0);
	cout << sum << endl;
}