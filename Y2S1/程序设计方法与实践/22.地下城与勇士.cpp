#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int n, m, k;
char Maze[110][110] = {0};
bool vis[110][110][70] = {0};
int op[5][5] = {{-1,0},{1,0},{0,-1},{0,1}};
int sx, sy;
int ex, ey;

struct coordinate{
	int x;
	int y;
	int move;
	
} now;

bool inMaze(int x, int y){
	if (x>=0&&x<n&&y>=0&&y<m)
		return true;
	else
		return false;
}

void bfs(){
	now.x = sx;
	now.y = sy; 
	now.move = 0;
	queue<coordinate> que;
	que.push(now);
	vis[sx][sy][now.move % k] = true;

	while (que.size()){
		now = que.front();
		que.pop();
		for (int i = 0; i < 4; i++){
			coordinate next;
			next.x = now.x + op[i][0];
			next.y = now.y + op[i][1];
			next.move = now.move + 1;
			
			if (!inMaze(next.x, next.y) || Maze[next.x][next.y] == '#') continue;
			if (vis[next.x][next.y][next.move % k]) continue;
			if (Maze[next.x][next.y] == '*' && next.move % k != 0) continue;
			
			if (Maze[next.x][next.y] == 'E'){
				printf("%d\n", next.move);
				return;
			}
			
			vis[next.x][next.y][next.move % k] = true;
			que.push(next);
		}
	} 
	
	printf("-1\n");
	return;
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		memset(Maze, 0, sizeof(Maze));
		memset(vis, 0, sizeof(vis));
		scanf("%d %d %d", &n, &m, &k);
		getchar();
		for (int i = 0; i < n ;i++){
			for (int j = 0; j < m; j++){
				scanf("%c", &Maze[i][j]);
				if(Maze[i][j] == 'S'){
					sx = i;
					sy = j;
				}
				if(Maze[i][j] == 'E'){
					ex = i;
					ey = j;
				}	
			}
			getchar();
		}
		bfs();
	}
}