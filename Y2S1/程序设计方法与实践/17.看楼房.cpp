#include<iostream>
#include<cstring>
#include<algorithm>
#include<stack>

using namespace std;

struct building{
	long long color;
	long long height;
}No[1000010];


int Color[1000010] = {0};
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		int total = 0;
		int flag = 0, flag2 = 0;
		memset(Color, 0, sizeof(Color));
		stack<long long> staHeight;
		stack<long long> staColor;
		scanf("%d",&n);
		for (long long i = 0; i < n; i++){
			scanf("%lld", &No[i].color);
		}
		for (long long i = 0; i < n; i++){
			scanf("%lld", &No[i].height);
			if (staHeight.empty()){
				staHeight.push(No[i].height);
				staColor.push(No[i].color); 
				Color[No[i].color]++;
				total++;
			}
			else if (No[i].height < staHeight.top()){
				if (Color[No[i].color] == 0){
					staHeight.push(No[i].height);
					staColor.push(No[i].color); 
					Color[No[i].color]++;
					total++;
				}
			}
			else if (No[i].height == staHeight.top()){
				if (Color[No[i].color] != 0)
					total--;
			}
			else{
				while(!staHeight.empty() && No[i].height > staHeight.top()){
					staHeight.pop();
					Color[staColor.top()]--;
					staColor.pop();
					total--; 
				}
				total++;
				if (Color[No[i].color] != 0){
					total--;
				}
				else{
					staHeight.push(No[i].height);
					staColor.push(No[i].color);
					Color[No[i].color]++;					
				}

			}
			
			if (flag2)
				printf(" ");
			printf("%d",total);
			flag2 = 1;
		}
		printf("\n");
	}
}