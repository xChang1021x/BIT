#include<iostream>
#include<algorithm>
#include<stack>

using namespace std;

int main(){
	int n;
	while(~scanf("%d",&n)){
		stack<int> sta;
		int x, k = 0;
		for (int i = 0; i < n; i++){
			scanf("%d", &x);
			if (x % 2 == 0){
				sta.push(0);
				k++;			
			}
			else{
				sta.push(1);
				k++;			
			}

			if (k >= 2){
				int a, b;
				a = sta.top();
				sta.pop();
				b = sta.top();
				sta.pop();
				if (a == b){
					k -= 2;
				}
				else{
					sta.push(b);
					sta.push(a);
				}	
			}
			
		}
		if (sta.size() == 1 || sta.size() == 0){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
}