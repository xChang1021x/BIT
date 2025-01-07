#include <iostream>
#include <algorithm>

using namespace std;

int start[1000010] = {0};
int Etime[1000010] = {0};

int main(){

	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> start[i] >> Etime[i];
	}
	sort(start, start + n);
	sort(Etime, Etime + n);
	
	int i = 0, j = 0;
	int t = 0, sum = 0;
	while(i < n && j < n){
		if(start[i] < Etime[j]){
			t++;
			i++;
			sum = max(sum, t);
		}
		else if(start[i] > Etime[j]){
			t--;
			j++;
		}
		else{
			i++;
			j++;
			sum = max(sum, t);
		}
	}
	cout << sum << endl;
}