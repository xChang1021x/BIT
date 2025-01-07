#include<iostream>
#include<algorithm>

using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	int Height[10010] = {0};
	for (int i = 0; i < n; i++){
		cin >> Height[i];
	}
	
	for (int i = 0; i < n-1; i++){
		for (int j = i + 1; j < n; j++){
			if (Height[i] >= Height [j]){
				int temp;
				temp = Height[i];
				Height[i] = Height[j];
				Height[j] = temp;
			}
		}
	}
	
	for (int i = 0; i < n; i++){
		cout << Height[i];
	}
}