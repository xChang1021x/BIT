#include<iostream>
#include<cstring>
#include<algorithm>
#include<stack>
#include<utility>

using namespace std;

int n, flag = 0;
int Map[110][110] = {-1};
stack<pair<int, int> > Move;
int His[110][110] = {0};
int op[5][5] = {{1,0},{0,1},{-1,0},{0,-1}};

void Dfs(int x, int y){
	if (x == n && y == n || flag){
		flag = 1;
		return;
	}
	for (int i = 0; i < 4; i++){
		int nx, ny;
		nx = x + op[i][0];
		ny = y + op[i][1];
		if (Map[nx][ny] != 1 && Map[nx][ny] != -1 && !His[nx][ny]){
			His[nx][ny] = 1;
			pair<int, int> xy;
			xy.first = nx;
			xy.second = ny;
			Move.push(xy);
			Dfs(nx, ny);
			if (flag)
				return;
			Move.pop();
		} 	
	}
}

int main(){
	memset(His, 0, sizeof(His));
	memset(Map, -1, sizeof(His));
	scanf("%d %d", &n, &n);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			scanf("%d", &Map[i][j]);
		}
	}
	His[1][1] = 1;
	Dfs(1, 1);
	
	if(!Move.size()){
		printf("There is no solution!\n");
		return 0;
	}
	
	stack<pair<int, int> > Arrange;
	pair<int, int> xy;
	while(Move.size()){
		Arrange.push(Move.top());
		Move.pop();
	}
	printf("<1,1> ");
	while(Arrange.size()){
		xy = Arrange.top();
		printf("<%d,%d> ", xy.first, xy.second);
		Arrange.pop();
	}
	printf("\n");
	return 0;
}

