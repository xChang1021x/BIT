#include<iostream>
#include<algorithm>
#include<stack>

using namespace std;

int main(){
	int n;
	while(~scanf("%d",&n)){
		stack<int> sta;
		int x, z = 0, pre, k = 0, max = 0, flag = 1;

		for (int i = 0; i < n; i++){
			scanf("%d", &x);
			max = max > x ? max : x;
			sta.push(x);
			k++; 
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
			if (!sta.empty())
				pre = sta.top();			
			if (pre < x)
				flag = 0;	
		}
		
		if (sta.size() == 0 && flag){
			printf("YES\n");
		}
		else if (sta.size() == 1 && sta.top() >= max && flag){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
}