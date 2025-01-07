#include<iostream>
#include<queue>

using namespace std;


const int MAX = 0x3F3F3F;
int map[1010][1010] = {0};
int dis[1010];
bool vis[1010];
int n, m;

void dijkstra(int s){
	for (int i = 0; i < n; i++)
	{
		dis[i] = map[s][i];
		vis[i] = false;
	}
	dis[s] = 0;
	vis[s] = true;
	for (int i = 0; i < n; i++)
	{
		int temp = MAX, v;
		for (int j = 0; j < n; j++)
		{
			if (!vis[j] && temp > dis[j])
			{
				temp = dis[j];
				v = j;
			}
		}
		if (temp == MAX)
			break;
		vis[v] = true;
		for (int j = 0; j < n; j++)
		{
			if (!vis[j] && dis[v] + map[v][j] < dis[j])
			{
				dis[j] = dis[v] + map[v][j];
			}
		}
	}
}

int main(){
	char start;
	int sum = 0;
	scanf("%d,%d,%c", &n, &m, &start);
	getchar();
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			map[i][j] = i==j? 0 : MAX;
		}
	}
	for (int i = 0; i < m; i++){
		char a, b;
		int temp;
		scanf("<%c,%c,%d>", &a, &b, &temp);
		getchar();
		int x = a - 'a';
		int y = b - 'a';
		map[x][y] = temp;
	}
	dijkstra(start - 'a');
	for (int i = 0; i < n; i++){
		printf("%c:%d\n", 'a'+i, dis[i]);
	}
	return 0;
}