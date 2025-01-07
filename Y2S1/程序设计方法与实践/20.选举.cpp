#include<iostream>
#include<queue>

using namespace std;

int main(){
	int n, cnt = 0, cnt2 = 0;
	int killX = 0, killD = 0;
	int cntD = 0, cntX = 0;
	char x, y;
	scanf("%d", &n);
	getchar();
	queue<char> que;
	queue<char> que2;
	for (int i = 0; i < n; i++){
		scanf("%c", &x);
		que.push(x); 
		if (x == 'D')
			cntD++;
		else
			cntX++;
	}
	while(cntD != 0 && cntX != 0){	
		x = que.front();
		que.pop();
		if (x == 'D'){
			if (killD > cnt){
				killD--;
				cntD--;
			}
			else{
				killX++;	
				que2.push(x);
				cnt++;
			}
		}
		else{
			if (killX > cnt2){
				killX--;
				cntX--;
			}
			else{
				killD++;	
				que2.push(x);
				cnt2++;
			}
		}

		if (que.empty()){
			while (!que2.empty()){
				while (killX != 0 && que2.front() == 'X'){
					que2.pop();
					killX--;
					cntX--;
					if (que2.empty())
						break;
				}
				while (killD != 0 && que2.front() == 'D'){
					que2.pop();
					killD--;
					cntD--;
					if (que2.empty())
						break;
				}
				
				
				que.push(que2.front());
				que2.pop(); 
				cnt = 0;
				cnt2 = 0;
			}
		}
		
		
	}
	printf("%c\n",que.front());
}