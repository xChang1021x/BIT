#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

struct Edge{
	int x;
	int y;
	int weight;
}edges[1010];

int n, m;
int tree[1010];

int cmp(const void *a, const void *b){
	Edge *pa = (Edge *)a;
	Edge *pb = (Edge *)b;
	return (int)pa->weight-(int)pb->weight;
}

void init(){
	for (int i = 0; i <= n; i++)
		tree[i] = i;
}

int find(int n){
	if (tree[n] == n)
		return n;
	else
		return tree[n] = find(tree[n]);
}

int judge(int x, int y){
	int a = find(x);
	int b = find(y);
	if (a != b){
		tree[a] = b;
		return 1;
	}
	else
		return 0;
}

void kruskal(){
	int side = 0;
	int sum = 0;
	init();
	for (int i = 0; i < m; i++){
		if (judge(edges[i].x, edges[i].y)){
			side++;
			sum += edges[i].weight;
		}
		if (side == n - 1)
			break;
	}
	if (side != n - 1)
		cout << "-1" << endl;
	else
		cout << sum << endl;
}

int main(){

	cin >> n >> m;
	for (int i = 0; i < m; i++){
		cin >> edges[i].x >> edges[i].y >> edges[i].weight;
	}
	
	qsort(edges, m, sizeof(Edge), cmp);
	kruskal();
	return 0;
}