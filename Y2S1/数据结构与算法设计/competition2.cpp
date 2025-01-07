#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

struct Mission{
	int time;
	int value;
} mission[10010];

int cmp(const void* a, const void* b)
{
    Mission* pa = (Mission*)a;
    Mission* pb = (Mission*)b;
    int num1 = pa->time;
    int num2 = pb->time;
    if (num1 == num2){
    	num1 = pa->value;
    	num2 = pb->value;
    	return (int)num2 - num1;
	}
    else return (int)num1 - num2;   
}

int main()
{
	int t[10010] = {0};
	int record[10010] = {0};
	int lianxu[10010] = {0};
	int n, m, q;
	cin >> n >> m >> q;
	for (int i = 0; i < q; i++){
		cin >> t[i]; 
	}
	for (int i = 0; i < m; i++){
		int x;
		cin >> x >> mission[i].value;
		mission[i].time = (int)pow(2, x);
		record[x]++;
	}
	
	qsort(mission, m, sizeof(Mission), cmp);
	
	int cnt = 0, k = 0, l = 0;;
	for(int i = 1; i <= n; i++){
		if (i == t[k]){
			if (cnt != 0)
				lianxu[l++] = cnt;
			cnt = 0;
			k++;
		}
		else{
			cnt++;
		}
	}
	if (cnt != 0)
		lianxu[l++] = cnt;
	
	sort(lianxu, lianxu + l);
	
	int Answer = 0, z = 0;
	for (int i = 0; i < m; i++){
		if (mission[i].time == lianxu[z]){
			Answer += mission[i].value;
			z++;
		}
		else if (mission[i].time > lianxu[z]){
			z++;
		}
		else{
			int temptime = 0, tempx = 0;
			for (int j = 0; j < lianxu[z]; j++){
				
			}
		}
	}
	
	for (int i = 0; i < l; i++){
		cout << lianxu[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < m; i++){
		cout << mission[i].time << " " << mission[i].value << "\n";
	}
}