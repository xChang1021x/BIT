#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int n, m, k;
char Maze[1010][1010] = {0};
int vis[1010][1010] = {0};
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
	memset(vis, -1, sizeof(vis));
	now.x = sx;
	now.y = sy; 
	now.move = 0;
	queue<coordinate> que;
	que.push(now);
	vis[sx][sy] = 0;

	while (que.size()){
		now = que.front();
		que.pop();

		for (int i = 0; i < 4; i++){
			coordinate next;
			for (int j = 0; j < k; j++){
				next.x = now.x + op[i][0] * (j + 1);
				next.y = now.y + op[i][1] * (j + 1);
				
				if (!inMaze(next.x, next.y) || Maze[next.x][next.y] == '#') break;
				if (vis[next.x][next.y] >= 0) continue;
				
				
				vis[next.x][next.y] = vis[now.x][now.y] + 1;
				que.push(next);	
				if (next.x == ex && next.y == ey){
					printf("%d\n", vis[ex][ey]);
					return;
				}	
			}
			

		}
	} 
	
	printf("-1\n");
	return;
}

int main(){
	memset(Maze, 0, sizeof(Maze));
	memset(vis, 0, sizeof(vis));
	scanf("%d %d %d", &n, &m, &k);
	getchar();
	for (int i = 0; i < n ;i++){
		for (int j = 0; j < m; j++){
			scanf("%c", &Maze[i][j]);
		}
		getchar();
	}
	scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
	sx--;
	sy--;
	ex--;
	ey--;
	bfs();
}