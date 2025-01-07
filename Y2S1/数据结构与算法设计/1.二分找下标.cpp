#include <iostream>
#include <algorithm>

using namespace std;

int a[1000010], flag=1;


int main(){
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		scanf("%d", &a[i]);
		if (a[i] == i){
			flag = 0;
			cout << i << " ";
		}
	}
	if (flag){
		cout << "No" << endl;
	}
	else cout << endl;
}