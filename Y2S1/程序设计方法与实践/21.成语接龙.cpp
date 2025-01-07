#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map>

using namespace std;

int n, m, k;
bool vis[1000010] = {0};
map<int, vector<int> > Word;
int sf, sl;
int ef, el;

struct node{
	int head;
	int tail;
	int move;
} now;


void bfs(){
	
	now.head = sf;
	now.tail = sl;
	now.move = 1;
	vis[now.tail] = true;
	
	queue<node> que;
	que.push(now);
	
	if (now.head == ef && now.tail == el){
		printf("%d\n",now.move);
		return;
	}
	
	while (que.size()){
		now = que.front();
		que.pop();
		
		
		for (int i = 0; i < Word[now.tail].size(); i++){
			node next;
			next.head = now.tail;
			next.tail = Word[now.tail][i];
			next.move = now.move + 1;
			if (next.head == ef && next.tail == el){
				printf("%d\n",next.move);
				return;
			}
			
			if (vis[Word[now.tail][i]]) continue;
			
			que.push(next);
			vis[next.tail] = true;
			
			
		}
		
	} 
	
	printf("-1\n");
	return;
}

int main(){
	int a,b,c;
	scanf("%d", &n);
	for (int i = 0; i < n ;i++){
		scanf("%d %d %d %d", &a, &b, &b, &c);
		Word[a].push_back(c);
	}
	scanf("%d %d %d %d", &sf, &a, &a, &sl);
	scanf("%d %d %d %d", &ef, &a, &a, &el);
	
	bfs();
}